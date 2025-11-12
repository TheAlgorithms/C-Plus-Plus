package cmd

import (
	"fmt"
	"path/filepath"
	"strconv"
	"strings"

	"github.com/DataZimbo/diskscan/pkg/scanner"
	"github.com/DataZimbo/diskscan/pkg/ui"
	"github.com/spf13/cobra"
)

var scanCmd = &cobra.Command{
	Use:   "scan [path]",
	Short: "Scan a directory or disk",
	Long:  `Scan a directory or disk and display space usage information.`,
	Args:  cobra.MaximumNArgs(1),
	Run:   runScan,
}

func init() {
	rootCmd.AddCommand(scanCmd)

	scanCmd.Flags().IntVarP(&depth, "depth", "d", 3, "Maximum depth to display")
	scanCmd.Flags().StringVarP(&minSize, "min-size", "m", "1MB", "Minimum size to display (e.g., 1KB, 10MB, 1GB)")
	scanCmd.Flags().IntVarP(&topN, "top", "t", 10, "Number of top items to show")
	scanCmd.Flags().BoolVarP(&showChart, "chart", "c", true, "Show bar chart")
}

func runScan(cmd *cobra.Command, args []string) {
	// Determine path to scan
	path := "."
	if len(args) > 0 {
		path = args[0]
	}

	// Resolve absolute path
	absPath, err := filepath.Abs(path)
	checkError(err)

	// Display welcome
	if !noColor {
		ui.DisplayWelcome()
	}

	// Parse minimum size
	minSizeBytes := parseSize(minSize)

	// Create scanner
	fmt.Printf("🔍 Scanning %s...\n", absPath)
	s := scanner.NewScanner(workers)

	// Set progress callback
	s.SetProgressCallback(func(scanned int64, path string) {
		if scanned%1000 == 0 {
			ui.ClearLine()
			fmt.Printf("\r📊 Scanned %d files...", scanned)
		}
	})

	// Perform scan
	root, err := s.Scan(absPath)
	checkError(err)

	ui.ClearLine()

	// Get disk info
	diskInfo, err := scanner.GetDiskInfo(absPath)
	if err == nil {
		diskInfo.CalculateHiddenSpace(root.Size)
	}

	// Display results
	ui.DisplaySummary(root, diskInfo)

	if showChart {
		ui.DisplayBarChart(root, topN)
	}

	ui.DisplayTopDirs(root, topN)
	ui.DisplayTopFiles(root, topN)

	// Display tree
	fmt.Printf("\n%s=== Directory Tree ===%s\n\n", ui.ColorBold, ui.ColorReset)
	ui.DisplayTree(root, depth, minSizeBytes)

	// Display errors if any
	errors := s.GetErrors()
	if len(errors) > 0 {
		ui.DisplayErrors(errors, 10)
	}

	fmt.Printf("\n✅ Scan complete! Use 'diskscan analyze %s' for interactive mode.\n\n", absPath)
}

// parseSize parses a size string like "10MB" into bytes
func parseSize(sizeStr string) int64 {
	sizeStr = strings.ToUpper(strings.TrimSpace(sizeStr))

	multipliers := map[string]int64{
		"B":  1,
		"KB": 1024,
		"MB": 1024 * 1024,
		"GB": 1024 * 1024 * 1024,
		"TB": 1024 * 1024 * 1024 * 1024,
	}

	for suffix, multiplier := range multipliers {
		if strings.HasSuffix(sizeStr, suffix) {
			numStr := strings.TrimSuffix(sizeStr, suffix)
			num, err := strconv.ParseFloat(numStr, 64)
			if err != nil {
				return 1024 * 1024 // Default to 1MB
			}
			return int64(num * float64(multiplier))
		}
	}

	// Try parsing as raw number
	num, err := strconv.ParseInt(sizeStr, 10, 64)
	if err != nil {
		return 1024 * 1024 // Default to 1MB
	}
	return num
}
