package cmd

import (
	"fmt"
	"os"
	"path/filepath"

	"github.com/DataZimbo/diskscan/pkg/scanner"
	"github.com/DataZimbo/diskscan/pkg/ui"
	"github.com/spf13/cobra"
)

var infoCmd = &cobra.Command{
	Use:   "info [path]",
	Short: "Display disk information",
	Long:  `Display detailed information about a disk or filesystem.`,
	Args:  cobra.MaximumNArgs(1),
	Run:   runInfo,
}

func init() {
	rootCmd.AddCommand(infoCmd)
}

func runInfo(cmd *cobra.Command, args []string) {
	// Determine path
	path := "."
	if len(args) > 0 {
		path = args[0]
	}

	// Resolve absolute path
	absPath, err := filepath.Abs(path)
	checkError(err)

	// Check if path exists
	if _, err := os.Stat(absPath); err != nil {
		checkError(fmt.Errorf("cannot access path: %w", err))
	}

	// Get disk info
	diskInfo, err := scanner.GetDiskInfo(absPath)
	checkError(err)

	// Display disk information
	fmt.Printf("\n%s=== Disk Information ===%s\n\n", ui.ColorBold, ui.ColorReset)
	fmt.Printf("📂 Path:         %s\n", absPath)
	fmt.Printf("💾 File System:  %s\n", diskInfo.FileSystem)
	fmt.Printf("\n")
	fmt.Printf("📦 Total Space:  %s\n", scanner.FormatSize(diskInfo.TotalSize))
	fmt.Printf("✅ Used Space:   %s (%.1f%%)\n",
		scanner.FormatSize(diskInfo.UsedSize),
		scanner.GetPercentage(diskInfo.UsedSize, diskInfo.TotalSize))
	fmt.Printf("🆓 Free Space:   %s (%.1f%%)\n",
		scanner.FormatSize(diskInfo.FreeSize),
		scanner.GetPercentage(diskInfo.FreeSize, diskInfo.TotalSize))

	// Display visual bar
	fmt.Println()
	displayUsageBar(diskInfo.UsedSize, diskInfo.TotalSize)
	fmt.Println()

	// Quick scan option
	fmt.Println("\n💡 Tip: Run 'diskscan scan .' to analyze what's using the space")
}

func displayUsageBar(used, total int64) {
	width := 50
	percentage := scanner.GetPercentage(used, total)
	filled := int(percentage / 100.0 * float64(width))

	usedBar := ""
	freeBar := ""

	for i := 0; i < filled; i++ {
		usedBar += "█"
	}
	for i := 0; i < width-filled; i++ {
		freeBar += "░"
	}

	color := ui.ColorGreen
	if percentage >= 90 {
		color = ui.ColorRed
	} else if percentage >= 75 {
		color = ui.ColorYellow
	}

	fmt.Printf("[%s%s%s%s] %.1f%% used\n", color, usedBar, ui.ColorReset, freeBar, percentage)
}
