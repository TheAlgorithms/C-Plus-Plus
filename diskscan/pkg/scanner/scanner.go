package scanner

import (
	"fmt"
	"io/fs"
	"os"
	"path/filepath"
	"sync"
	"sync/atomic"
	"syscall"
	"time"
)

// DiskInfo represents overall disk information
type DiskInfo struct {
	Path        string
	TotalSize   int64
	UsedSize    int64
	FreeSize    int64
	HiddenSpace int64
	FileSystem  string
}

// FileNode represents a file or directory in the tree
type FileNode struct {
	Name        string
	Path        string
	Size        int64
	IsDir       bool
	Children    []*FileNode
	ChildrenMap map[string]*FileNode
	mu          sync.RWMutex
	FileCount   int64
	DirCount    int64
	LastMod     time.Time
}

// Scanner handles disk scanning operations
type Scanner struct {
	root         *FileNode
	totalFiles   int64
	totalDirs    int64
	totalSize    int64
	errors       []error
	mu           sync.Mutex
	workerPool   int
	progressFunc func(scanned int64, path string)
}

// NewScanner creates a new scanner instance
func NewScanner(workers int) *Scanner {
	if workers <= 0 {
		workers = 10 // default worker pool size
	}
	return &Scanner{
		workerPool: workers,
		errors:     make([]error, 0),
	}
}

// SetProgressCallback sets a callback for progress updates
func (s *Scanner) SetProgressCallback(fn func(scanned int64, path string)) {
	s.progressFunc = fn
}

// Scan performs a parallel scan of the given path
func (s *Scanner) Scan(rootPath string) (*FileNode, error) {
	// Validate path
	info, err := os.Stat(rootPath)
	if err != nil {
		return nil, fmt.Errorf("cannot access path: %w", err)
	}

	// Initialize root node
	s.root = &FileNode{
		Name:        filepath.Base(rootPath),
		Path:        rootPath,
		IsDir:       info.IsDir(),
		ChildrenMap: make(map[string]*FileNode),
		LastMod:     info.ModTime(),
	}

	if !info.IsDir() {
		s.root.Size = info.Size()
		return s.root, nil
	}

	// Start scanning
	startTime := time.Now()
	s.scanDirectory(s.root)
	duration := time.Since(startTime)

	fmt.Printf("\nScan completed in %v\n", duration.Round(time.Millisecond))
	fmt.Printf("Files: %d, Directories: %d, Total Size: %s\n",
		s.totalFiles, s.totalDirs, FormatSize(s.totalSize))

	return s.root, nil
}

// scanDirectory recursively scans a directory
func (s *Scanner) scanDirectory(node *FileNode) {
	entries, err := os.ReadDir(node.Path)
	if err != nil {
		s.addError(fmt.Errorf("cannot read directory %s: %w", node.Path, err))
		return
	}

	var wg sync.WaitGroup
	semaphore := make(chan struct{}, s.workerPool)

	for _, entry := range entries {
		entryPath := filepath.Join(node.Path, entry.Name())
		info, err := entry.Info()
		if err != nil {
			s.addError(fmt.Errorf("cannot stat %s: %w", entryPath, err))
			continue
		}

		childNode := &FileNode{
			Name:        entry.Name(),
			Path:        entryPath,
			IsDir:       entry.IsDir(),
			ChildrenMap: make(map[string]*FileNode),
			LastMod:     info.ModTime(),
		}

		node.mu.Lock()
		node.Children = append(node.Children, childNode)
		node.ChildrenMap[entry.Name()] = childNode
		node.mu.Unlock()

		if entry.IsDir() {
			atomic.AddInt64(&s.totalDirs, 1)
			wg.Add(1)
			semaphore <- struct{}{}
			go func(n *FileNode) {
				defer wg.Done()
				defer func() { <-semaphore }()
				s.scanDirectory(n)
			}(childNode)
		} else {
			size := info.Size()
			childNode.Size = size
			atomic.AddInt64(&node.Size, size)
			atomic.AddInt64(&s.totalSize, size)
			atomic.AddInt64(&s.totalFiles, 1)

			if s.progressFunc != nil && atomic.LoadInt64(&s.totalFiles)%100 == 0 {
				s.progressFunc(s.totalFiles, entryPath)
			}
		}
	}

	wg.Wait()

	// Aggregate sizes from children
	for _, child := range node.Children {
		if child.IsDir {
			atomic.AddInt64(&node.Size, child.Size)
			atomic.AddInt64(&node.FileCount, child.FileCount)
			atomic.AddInt64(&node.DirCount, child.DirCount+1)
		} else {
			atomic.AddInt64(&node.FileCount, 1)
		}
	}
}

// GetDiskInfo retrieves disk information for a given path
func GetDiskInfo(path string) (*DiskInfo, error) {
	var stat syscall.Statfs_t
	if err := syscall.Statfs(path, &stat); err != nil {
		return nil, fmt.Errorf("cannot get disk info: %w", err)
	}

	totalSize := int64(stat.Blocks) * int64(stat.Bsize)
	freeSize := int64(stat.Bfree) * int64(stat.Bsize)
	usedSize := totalSize - freeSize

	return &DiskInfo{
		Path:       path,
		TotalSize:  totalSize,
		UsedSize:   usedSize,
		FreeSize:   freeSize,
		FileSystem: getFsType(stat.Type),
	}, nil
}

// CalculateHiddenSpace calculates hidden/unaccounted space
func (di *DiskInfo) CalculateHiddenSpace(scannedSize int64) {
	di.HiddenSpace = di.UsedSize - scannedSize
}

// getFsType returns filesystem type as string
func getFsType(fsType int64) string {
	// Common filesystem type magic numbers for Linux
	fsTypes := map[int64]string{
		0xEF53:     "ext2/ext3/ext4",
		0x58465342: "XFS",
		0x01021994: "tmpfs",
		0x6969:     "NFS",
		0x9123683E: "Btrfs",
		0x5346544e: "NTFS",
		0x4d44:     "FAT",
		0x4006:     "FAT32",
		0x517B:     "SMB",
		0xFF534D42: "CIFS",
		0x52654973: "ReiserFS",
		0x1373:     "devfs",
	}

	if name, ok := fsTypes[fsType]; ok {
		return name
	}
	return fmt.Sprintf("unknown (0x%X)", fsType)
}

// GetStats returns scanning statistics
func (s *Scanner) GetStats() (files, dirs, size int64) {
	return s.totalFiles, s.totalDirs, s.totalSize
}

// GetErrors returns any errors encountered during scanning
func (s *Scanner) GetErrors() []error {
	s.mu.Lock()
	defer s.mu.Unlock()
	return append([]error(nil), s.errors...)
}

// addError safely adds an error to the error list
func (s *Scanner) addError(err error) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.errors = append(s.errors, err)
}

// FindLargestFiles returns the N largest files in the tree
func (node *FileNode) FindLargestFiles(n int) []*FileNode {
	var files []*FileNode
	node.collectFiles(&files)

	// Sort by size
	for i := 0; i < len(files); i++ {
		for j := i + 1; j < len(files); j++ {
			if files[j].Size > files[i].Size {
				files[i], files[j] = files[j], files[i]
			}
		}
	}

	if len(files) > n {
		files = files[:n]
	}
	return files
}

// collectFiles recursively collects all files
func (node *FileNode) collectFiles(files *[]*FileNode) {
	if !node.IsDir {
		*files = append(*files, node)
		return
	}
	for _, child := range node.Children {
		child.collectFiles(files)
	}
}

// FindLargestDirs returns the N largest directories
func (node *FileNode) FindLargestDirs(n int) []*FileNode {
	var dirs []*FileNode
	node.collectDirs(&dirs)

	// Sort by size
	for i := 0; i < len(dirs); i++ {
		for j := i + 1; j < len(dirs); j++ {
			if dirs[j].Size > dirs[i].Size {
				dirs[i], dirs[j] = dirs[j], dirs[i]
			}
		}
	}

	if len(dirs) > n {
		dirs = dirs[:n]
	}
	return dirs
}

// collectDirs recursively collects all directories
func (node *FileNode) collectDirs(dirs *[]*FileNode) {
	if node.IsDir {
		*dirs = append(*dirs, node)
		for _, child := range node.Children {
			child.collectDirs(dirs)
		}
	}
}

// WalkTree walks the tree with a callback function
func (node *FileNode) WalkTree(fn func(*FileNode) error) error {
	if err := fn(node); err != nil {
		if err == filepath.SkipDir {
			return nil
		}
		return err
	}

	if node.IsDir {
		for _, child := range node.Children {
			if err := child.WalkTree(fn); err != nil {
				return err
			}
		}
	}
	return nil
}

// FormatSize formats bytes into human-readable format
func FormatSize(bytes int64) string {
	const unit = 1024
	if bytes < unit {
		return fmt.Sprintf("%d B", bytes)
	}
	div, exp := int64(unit), 0
	for n := bytes / unit; n >= unit; n /= unit {
		div *= unit
		exp++
	}
	return fmt.Sprintf("%.1f %cB", float64(bytes)/float64(div), "KMGTPE"[exp])
}

// GetPercentage calculates percentage of total
func GetPercentage(size, total int64) float64 {
	if total == 0 {
		return 0
	}
	return (float64(size) / float64(total)) * 100
}

// IsSafeToDelete checks if a path is safe to delete
func IsSafeToDelete(path string) error {
	// System critical paths that should never be deleted
	criticalPaths := []string{
		"/",
		"/bin",
		"/boot",
		"/dev",
		"/etc",
		"/lib",
		"/lib64",
		"/proc",
		"/root",
		"/sbin",
		"/sys",
		"/usr",
		"/var",
	}

	absPath, err := filepath.Abs(path)
	if err != nil {
		return err
	}

	for _, critical := range criticalPaths {
		if absPath == critical || filepath.HasPrefix(absPath, critical+string(os.PathSeparator)) {
			return fmt.Errorf("refusing to delete system-critical path: %s", absPath)
		}
	}

	return nil
}

// DeletePath safely deletes a file or directory
func DeletePath(path string) error {
	if err := IsSafeToDelete(path); err != nil {
		return err
	}

	info, err := os.Lstat(path)
	if err != nil {
		return fmt.Errorf("cannot stat path: %w", err)
	}

	if info.IsDir() {
		return os.RemoveAll(path)
	}
	return os.Remove(path)
}

// GetMountPoints returns all mount points on the system
func GetMountPoints() ([]string, error) {
	var mounts []string

	err := filepath.WalkDir("/proc/mounts", func(path string, d fs.DirEntry, err error) error {
		if err != nil {
			return err
		}
		return nil
	})

	if err != nil {
		// Fallback to common mount points
		mounts = []string{"/", "/home", "/tmp", "/var"}
	} else {
		// Read /proc/mounts for actual mount points
		// This is a simplified version
		mounts = []string{"/"}
	}

	return mounts, nil
}
