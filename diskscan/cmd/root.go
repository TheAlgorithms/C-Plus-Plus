package cmd

import (
	"fmt"
	"os"

	"github.com/spf13/cobra"
)

var (
	// Global flags
	workers   int
	depth     int
	minSize   string
	topN      int
	showChart bool
	noColor   bool
)

var rootCmd = &cobra.Command{
	Use:   "diskscan",
	Short: "DiskScan - Fast disk space analyzer",
	Long: `DiskScan is a high-performance disk space analyzer inspired by DaisyDisk.
It provides fast scanning, visual representation, and safe file management.

Features:
  • Parallel scanning for maximum speed
  • Visual tree and chart representations
  • Hidden space detection
  • Safe file deletion with safety checks
  • Support for multiple filesystems`,
	Version: "1.0.0",
}

func Execute() error {
	return rootCmd.Execute()
}

func init() {
	// Disable cobra's default completion command
	rootCmd.CompletionOptions.DisableDefaultCmd = true

	// Global flags
	rootCmd.PersistentFlags().IntVarP(&workers, "workers", "w", 10, "Number of parallel workers")
	rootCmd.PersistentFlags().BoolVar(&noColor, "no-color", false, "Disable colored output")
}

func checkError(err error) {
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error: %v\n", err)
		os.Exit(1)
	}
}
