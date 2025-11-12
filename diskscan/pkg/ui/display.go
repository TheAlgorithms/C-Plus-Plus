package ui

import (
	"fmt"
	"sort"
	"strings"

	"github.com/DataZimbo/diskscan/pkg/scanner"
)

// Color codes for terminal output
const (
	ColorReset  = "\033[0m"
	ColorRed    = "\033[31m"
	ColorGreen  = "\033[32m"
	ColorYellow = "\033[33m"
	ColorBlue   = "\033[34m"
	ColorPurple = "\033[35m"
	ColorCyan   = "\033[36m"
	ColorWhite  = "\033[37m"
	ColorBold   = "\033[1m"
)

// DisplayTree displays the file tree with sizes
func DisplayTree(node *scanner.FileNode, maxDepth int, minSize int64) {
	displayTreeRecursive(node, "", 0, maxDepth, minSize, node.Size)
}

func displayTreeRecursive(node *scanner.FileNode, prefix string, depth, maxDepth int, minSize, totalSize int64) {
	if depth > maxDepth && maxDepth > 0 {
		return
	}

	if node.Size < minSize {
		return
	}

	// Calculate percentage
	percentage := scanner.GetPercentage(node.Size, totalSize)

	// Color based on size percentage
	color := getColorForPercentage(percentage)

	// Display node
	icon := "📄"
	if node.IsDir {
		icon = "📁"
	}

	fmt.Printf("%s%s %s%s%s %s (%.1f%%)\n",
		prefix,
		icon,
		color,
		node.Name,
		ColorReset,
		scanner.FormatSize(node.Size),
		percentage,
	)

	if !node.IsDir {
		return
	}

	// Sort children by size
	children := make([]*scanner.FileNode, len(node.Children))
	copy(children, node.Children)
	sort.Slice(children, func(i, j int) bool {
		return children[i].Size > children[j].Size
	})

	// Display children
	for i, child := range children {
		isLast := i == len(children)-1
		childPrefix := prefix
		if isLast {
			childPrefix += "└── "
		} else {
			childPrefix += "├── "
		}

		newPrefix := prefix
		if isLast {
			newPrefix += "    "
		} else {
			newPrefix += "│   "
		}

		displayTreeRecursive(child, childPrefix, depth+1, maxDepth, minSize, totalSize)
	}
}

// DisplaySummary displays a summary of the scan
func DisplaySummary(node *scanner.FileNode, diskInfo *scanner.DiskInfo) {
	fmt.Printf("\n%s=== Disk Scan Summary ===%s\n\n", ColorBold, ColorReset)
	fmt.Printf("📂 Root Path:    %s\n", node.Path)
	fmt.Printf("📊 Total Size:   %s\n", scanner.FormatSize(node.Size))
	fmt.Printf("📄 Files:        %d\n", node.FileCount)
	fmt.Printf("📁 Directories:  %d\n", node.DirCount)

	if diskInfo != nil {
		fmt.Printf("\n%s=== Disk Information ===%s\n\n", ColorBold, ColorReset)
		fmt.Printf("💾 File System:  %s\n", diskInfo.FileSystem)
		fmt.Printf("📦 Total Space:  %s\n", scanner.FormatSize(diskInfo.TotalSize))
		fmt.Printf("✅ Used Space:   %s (%.1f%%)\n",
			scanner.FormatSize(diskInfo.UsedSize),
			scanner.GetPercentage(diskInfo.UsedSize, diskInfo.TotalSize))
		fmt.Printf("🆓 Free Space:   %s (%.1f%%)\n",
			scanner.FormatSize(diskInfo.FreeSize),
			scanner.GetPercentage(diskInfo.FreeSize, diskInfo.TotalSize))

		if diskInfo.HiddenSpace > 0 {
			fmt.Printf("❓ Hidden Space: %s%s%s (%.1f%%)\n",
				ColorYellow,
				scanner.FormatSize(diskInfo.HiddenSpace),
				ColorReset,
				scanner.GetPercentage(diskInfo.HiddenSpace, diskInfo.UsedSize))
			fmt.Printf("   %s(Space not accounted for by scanned files)%s\n", ColorYellow, ColorReset)
		}
	}
	fmt.Println()
}

// DisplayTopFiles displays the largest files
func DisplayTopFiles(node *scanner.FileNode, n int) {
	files := node.FindLargestFiles(n)
	if len(files) == 0 {
		return
	}

	fmt.Printf("\n%s=== Top %d Largest Files ===%s\n\n", ColorBold, n, ColorReset)
	for i, file := range files {
		percentage := scanner.GetPercentage(file.Size, node.Size)
		color := getColorForPercentage(percentage)
		fmt.Printf("%2d. %s%s%s\n", i+1, color, file.Path, ColorReset)
		fmt.Printf("    Size: %s (%.2f%%)\n", scanner.FormatSize(file.Size), percentage)
	}
	fmt.Println()
}

// DisplayTopDirs displays the largest directories
func DisplayTopDirs(node *scanner.FileNode, n int) {
	dirs := node.FindLargestDirs(n)
	if len(dirs) == 0 {
		return
	}

	fmt.Printf("\n%s=== Top %d Largest Directories ===%s\n\n", ColorBold, n, ColorReset)
	for i, dir := range dirs {
		if dir.Path == node.Path {
			continue // Skip root
		}
		percentage := scanner.GetPercentage(dir.Size, node.Size)
		color := getColorForPercentage(percentage)
		fmt.Printf("%2d. %s%s%s\n", i+1, color, dir.Path, ColorReset)
		fmt.Printf("    Size: %s (%.2f%%) - %d files, %d dirs\n",
			scanner.FormatSize(dir.Size), percentage, dir.FileCount, dir.DirCount)
	}
	fmt.Println()
}

// DisplayProgressBar displays a progress bar
func DisplayProgressBar(current, total int64, width int) {
	if total == 0 {
		return
	}

	percentage := float64(current) / float64(total)
	filled := int(percentage * float64(width))

	bar := strings.Repeat("█", filled) + strings.Repeat("░", width-filled)
	fmt.Printf("\r[%s] %.1f%% (%d/%d)", bar, percentage*100, current, total)
}

// DisplayBarChart displays a horizontal bar chart
func DisplayBarChart(node *scanner.FileNode, maxItems int) {
	if !node.IsDir || len(node.Children) == 0 {
		return
	}

	fmt.Printf("\n%s=== Space Distribution ===%s\n\n", ColorBold, ColorReset)

	// Sort children by size
	children := make([]*scanner.FileNode, len(node.Children))
	copy(children, node.Children)
	sort.Slice(children, func(i, j int) bool {
		return children[i].Size > children[j].Size
	})

	// Limit to maxItems
	if len(children) > maxItems {
		children = children[:maxItems]
	}

	// Find longest name for alignment
	maxNameLen := 0
	for _, child := range children {
		if len(child.Name) > maxNameLen {
			maxNameLen = len(child.Name)
		}
	}
	if maxNameLen > 30 {
		maxNameLen = 30
	}

	// Display bars
	barWidth := 50
	for _, child := range children {
		percentage := scanner.GetPercentage(child.Size, node.Size)
		color := getColorForPercentage(percentage)

		name := child.Name
		if len(name) > maxNameLen {
			name = name[:maxNameLen-3] + "..."
		}

		filled := int(percentage / 100.0 * float64(barWidth))
		if filled == 0 && child.Size > 0 {
			filled = 1
		}

		bar := strings.Repeat("█", filled)

		icon := "📄"
		if child.IsDir {
			icon = "📁"
		}

		fmt.Printf("%s %-*s %s%s%s %6.1f%% %s\n",
			icon,
			maxNameLen,
			name,
			color,
			bar,
			ColorReset,
			percentage,
			scanner.FormatSize(child.Size),
		)
	}
	fmt.Println()
}

// getColorForPercentage returns a color based on percentage
func getColorForPercentage(percentage float64) string {
	switch {
	case percentage >= 50:
		return ColorRed
	case percentage >= 20:
		return ColorYellow
	case percentage >= 5:
		return ColorCyan
	default:
		return ColorGreen
	}
}

// DisplayErrors displays any errors encountered during scanning
func DisplayErrors(errors []error, maxErrors int) {
	if len(errors) == 0 {
		return
	}

	fmt.Printf("\n%s⚠️  Errors encountered during scan:%s\n\n", ColorYellow, ColorReset)

	count := len(errors)
	if count > maxErrors {
		count = maxErrors
	}

	for i := 0; i < count; i++ {
		fmt.Printf("  • %s\n", errors[i])
	}

	if len(errors) > maxErrors {
		fmt.Printf("\n  ... and %d more errors\n", len(errors)-maxErrors)
	}
	fmt.Println()
}

// ClearLine clears the current line in terminal
func ClearLine() {
	fmt.Print("\r\033[K")
}

// ConfirmAction asks user for confirmation
func ConfirmAction(message string) bool {
	fmt.Printf("%s%s (y/N): %s", ColorYellow, message, ColorReset)
	var response string
	fmt.Scanln(&response)
	response = strings.ToLower(strings.TrimSpace(response))
	return response == "y" || response == "yes"
}

// DisplayWelcome displays a welcome message
func DisplayWelcome() {
	banner := `
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
`
	fmt.Println(ColorCyan + banner + ColorReset)
}
