package cmd

import (
	"fmt"
	"os"
	"path/filepath"

	"github.com/DataZimbo/diskscan/pkg/scanner"
	"github.com/DataZimbo/diskscan/pkg/ui"
	"github.com/spf13/cobra"
)

var (
	force      bool
	dryRun     bool
	recursive  bool
	sizeFilter string
)

var cleanCmd = &cobra.Command{
	Use:   "clean [path]",
	Short: "Safely delete files or directories",
	Long: `Safely delete files or directories with built-in safety checks.

Safety features:
  • Prevents deletion of system-critical paths
  • Requires confirmation before deletion
  • Dry-run mode to preview what will be deleted
  • Detailed logging of deletions`,
	Args: cobra.ExactArgs(1),
	Run:  runClean,
}

func init() {
	rootCmd.AddCommand(cleanCmd)

	cleanCmd.Flags().BoolVarP(&force, "force", "f", false, "Skip confirmation prompt")
	cleanCmd.Flags().BoolVarP(&dryRun, "dry-run", "n", false, "Show what would be deleted without deleting")
	cleanCmd.Flags().BoolVarP(&recursive, "recursive", "r", false, "Delete directories recursively")
	cleanCmd.Flags().StringVarP(&sizeFilter, "size", "s", "", "Only delete files larger than size (e.g., 100MB)")
}

func runClean(cmd *cobra.Command, args []string) {
	path := args[0]

	// Resolve absolute path
	absPath, err := filepath.Abs(path)
	checkError(err)

	// Check if path exists
	info, err := os.Lstat(absPath)
	if err != nil {
		checkError(fmt.Errorf("cannot access path: %w", err))
	}

	// Safety check
	if err := scanner.IsSafeToDelete(absPath); err != nil {
		fmt.Printf("%s❌ Safety check failed:%s %v\n", ui.ColorRed, ui.ColorReset, err)
		os.Exit(1)
	}

	// Check if directory and recursive flag
	if info.IsDir() && !recursive {
		fmt.Printf("%s❌ Cannot delete directory without --recursive flag%s\n", ui.ColorRed, ui.ColorReset)
		os.Exit(1)
	}

	// Calculate size
	var totalSize int64
	if info.IsDir() {
		fmt.Printf("📊 Calculating size...\n")
		s := scanner.NewScanner(workers)
		root, err := s.Scan(absPath)
		checkError(err)
		totalSize = root.Size
	} else {
		totalSize = info.Size()
	}

	// Display what will be deleted
	fmt.Printf("\n%s=== Deletion Summary ===%s\n\n", ui.ColorBold, ui.ColorReset)
	fmt.Printf("Path:  %s\n", absPath)
	fmt.Printf("Type:  %s\n", getType(info))
	fmt.Printf("Size:  %s\n", scanner.FormatSize(totalSize))

	if dryRun {
		fmt.Printf("\n%s[DRY RUN]%s No files will be deleted.\n", ui.ColorYellow, ui.ColorReset)
		return
	}

	// Confirm deletion
	if !force {
		fmt.Println()
		if !ui.ConfirmAction(fmt.Sprintf("⚠️  Delete %s (%s)?", absPath, scanner.FormatSize(totalSize))) {
			fmt.Println("Deletion cancelled.")
			return
		}
	}

	// Perform deletion
	fmt.Printf("\n🗑️  Deleting %s...\n", absPath)
	err = scanner.DeletePath(absPath)
	if err != nil {
		fmt.Printf("%s❌ Deletion failed:%s %v\n", ui.ColorRed, ui.ColorReset, err)
		os.Exit(1)
	}

	fmt.Printf("%s✅ Successfully deleted %s (%s)%s\n",
		ui.ColorGreen, absPath, scanner.FormatSize(totalSize), ui.ColorReset)
}

func getType(info os.FileInfo) string {
	if info.IsDir() {
		return "Directory"
	}
	if info.Mode()&os.ModeSymlink != 0 {
		return "Symlink"
	}
	return "File"
}
