# DiskScan 💿

A blazingly fast, cross-platform disk space analyzer inspired by DaisyDisk. Built with Go for maximum performance and portability.

## ✨ Features

- **🚀 Lightning Fast**: Parallel scanning using goroutines for optimal performance
- **📊 Visual Analysis**: Interactive charts and tree views of disk usage
- **🔍 Deep Inspection**: Find largest files and directories quickly
- **🛡️ Safe Deletion**: Built-in safety checks prevent accidental system damage
- **💾 Multi-Filesystem Support**: Works with ext4, NTFS, FAT, XFS, Btrfs, and more
- **❓ Hidden Space Detection**: Identifies unaccounted disk space
- **🎨 Beautiful Output**: Color-coded display with progress indicators
- **⚡ Interactive Mode**: Browse directory structure interactively

## 🎯 Tech Specs

### Supported Systems
- **Operating Systems**: Linux, macOS, Windows
- **Filesystems**:
  - Linux: ext2/ext3/ext4, XFS, Btrfs, NTFS, FAT32, tmpfs, NFS, CIFS
  - All FUSE-based filesystems
  - Network shares (NFS, SMB, CIFS)

### Performance
- Parallel scanning with configurable worker pool
- Optimized for SSDs and HDDs
- Minimal memory footprint
- Progress tracking for large scans

### Safety Features
- ✅ System-critical path protection
- ✅ Confirmation prompts before deletion
- ✅ Dry-run mode for testing
- ✅ No automatic cleaning
- ✅ User-controlled file operations

### Privacy
- ✅ Scans only file metadata (name, size, timestamps)
- ✅ Does not read file contents
- ✅ No data collection or transmission
- ✅ Completely offline operation

## 📦 Installation

### From Source

```bash
# Clone the repository
git clone https://github.com/DataZimbo/diskscan.git
cd diskscan

# Build the binary
go build -o diskscan

# Optional: Install globally
sudo mv diskscan /usr/local/bin/
```

### Using Go Install

```bash
go install github.com/DataZimbo/diskscan@latest
```

## 🚀 Quick Start

### Basic Usage

```bash
# Scan current directory
diskscan scan

# Scan specific path
diskscan scan /home/user/Documents

# Scan with custom depth
diskscan scan --depth 5 /var

# Show only items larger than 100MB
diskscan scan --min-size 100MB /home
```

### Interactive Mode

```bash
# Start interactive analysis
diskscan analyze /home/user

# Navigate directories, view charts, find largest files
# Commands: [number], u (up), t (top), c (chart), f (find), q (quit)
```

### Disk Information

```bash
# Show disk info for current path
diskscan info

# Show disk info for specific path
diskscan info /mnt/data
```

### Safe File Deletion

```bash
# Delete a file (with confirmation)
diskscan clean /path/to/file

# Delete directory recursively
diskscan clean --recursive /path/to/dir

# Dry-run (preview what would be deleted)
diskscan clean --dry-run /path/to/file

# Force deletion without confirmation
diskscan clean --force /path/to/file
```

## 📖 Command Reference

### Global Flags

```
--workers, -w    Number of parallel workers (default: 10)
--no-color       Disable colored output
--help, -h       Show help
--version        Show version
```

### Commands

#### `scan [path]`
Scan a directory and display space usage.

**Flags:**
- `--depth, -d`: Maximum tree depth to display (default: 3)
- `--min-size, -m`: Minimum size to display (default: 1MB)
- `--top, -t`: Number of top items to show (default: 10)
- `--chart, -c`: Show bar chart (default: true)

**Examples:**
```bash
diskscan scan /home/user
diskscan scan --depth 10 --min-size 500MB /var/log
diskscan scan --workers 20 --top 20 /mnt/backup
```

#### `analyze [path]`
Interactive mode for exploring disk usage.

**Examples:**
```bash
diskscan analyze
diskscan analyze /home/user/projects
```

**Interactive Commands:**
- `[number]` - Navigate into directory
- `u` - Go up one level
- `h` - Go to root
- `t` - Show top 10 largest items
- `c` - Show bar chart
- `f` - Find largest files globally
- `q` - Quit

#### `info [path]`
Display disk information and statistics.

**Examples:**
```bash
diskscan info
diskscan info /mnt/external
```

#### `clean <path>`
Safely delete files or directories.

**Flags:**
- `--force, -f`: Skip confirmation
- `--dry-run, -n`: Preview without deleting
- `--recursive, -r`: Delete directories recursively

**Examples:**
```bash
diskscan clean /tmp/cache
diskscan clean --recursive --dry-run /old/backups
diskscan clean --force /tmp/tempfile.txt
```

## 📊 Output Examples

### Scan Output

```
╔═══════════════════════════════════════════════════════════╗
║                                                           ║
║     ███████╗███████╗██╗     ██╗   ██╗███╗   ██╗         ║
║     ██╔════╝██╔════╝██║     ██║   ██║████╗  ██║         ║
║     █████╗  █████╗  ██║     ██║   ██║██╔██╗ ██║         ║
║     ██╔══╝  ██╔══╝  ██║     ██║   ██║██║╚██╗██║         ║
║     ██║     ███████╗███████╗╚██████╔╝██║ ╚████║         ║
║     ╚═╝     ╚══════╝╚══════╝ ╚═════╝ ╚═╝  ╚═══╝         ║
║                                                           ║
║            Fast Disk Space Analyzer                      ║
║                                                           ║
╚═══════════════════════════════════════════════════════════╝

🔍 Scanning /home/user...
Scan completed in 1.2s
Files: 15,432, Directories: 2,847, Total Size: 45.3 GB

=== Disk Scan Summary ===

📂 Root Path:    /home/user
📊 Total Size:   45.3 GB
📄 Files:        15,432
📁 Directories:  2,847

=== Disk Information ===

💾 File System:  ext4
📦 Total Space:  500.0 GB
✅ Used Space:   250.0 GB (50.0%)
🆓 Free Space:   250.0 GB (50.0%)

=== Space Distribution ===

📁 Documents      ████████████████████████████████████  65.2%  29.5 GB
📁 Downloads      ████████████████                      28.1%  12.7 GB
📁 Pictures       ███                                    4.3%   1.9 GB
📁 Videos         █                                      2.1%   950.0 MB
```

## 🏗️ Architecture

```
diskscan/
├── main.go                 # Entry point
├── cmd/                    # CLI commands
│   ├── root.go            # Root command setup
│   ├── scan.go            # Scan command
│   ├── analyze.go         # Interactive analysis
│   ├── clean.go           # Safe deletion
│   └── info.go            # Disk information
├── pkg/
│   ├── scanner/           # Core scanning logic
│   │   └── scanner.go    # Parallel scanner, disk info
│   └── ui/                # Display and formatting
│       └── display.go    # Tree, charts, progress
└── README.md
```

## 🔧 Development

### Prerequisites
- Go 1.21 or higher
- Linux, macOS, or Windows

### Building

```bash
# Build for current platform
go build -o diskscan

# Build with optimizations
go build -ldflags="-s -w" -o diskscan

# Cross-compile for Linux
GOOS=linux GOARCH=amd64 go build -o diskscan-linux

# Cross-compile for macOS
GOOS=darwin GOARCH=amd64 go build -o diskscan-macos

# Cross-compile for Windows
GOOS=windows GOARCH=amd64 go build -o diskscan.exe
```

### Testing

```bash
# Run tests
go test ./...

# Run with coverage
go test -cover ./...

# Run benchmarks
go test -bench=. ./...
```

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📝 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🙏 Acknowledgments

- Inspired by [DaisyDisk](https://daisydiskapp.com/)
- Built with [Cobra](https://github.com/spf13/cobra) for CLI
- Uses Go's excellent concurrency primitives

## 📞 Support

- 🐛 Report bugs via GitHub Issues
- 💡 Request features via GitHub Issues
- 📧 Contact: support@diskscan.io

## 🗺️ Roadmap

- [ ] Export reports to JSON/CSV
- [ ] Cloud storage integration (Dropbox, Google Drive, OneDrive)
- [ ] Duplicate file detection
- [ ] File type analysis
- [ ] Compression recommendations
- [ ] Scheduled scans
- [ ] Web UI dashboard
- [ ] Docker support
- [ ] Real-time monitoring

## ⚡ Performance Tips

1. **Increase workers for faster scans**: `--workers 20`
2. **Limit depth for quick overview**: `--depth 2`
3. **Use min-size to filter small files**: `--min-size 10MB`
4. **Run as root for full disk access**: `sudo diskscan scan /`

## 🔒 Security

- Never runs with unnecessary privileges
- No network access required
- No telemetry or tracking
- Open source and auditable

---

Made with ❤️ using Go
