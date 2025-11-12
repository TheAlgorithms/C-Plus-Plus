package cmd

import (
	"bufio"
	"fmt"
	"os"
	"path/filepath"
	"sort"
	"strconv"
	"strings"

	"github.com/DataZimbo/diskscan/pkg/scanner"
	"github.com/DataZimbo/diskscan/pkg/ui"
	"github.com/spf13/cobra"
)

var analyzeCmd = &cobra.Command{
	Use:   "analyze [path]",
	Short: "Interactive analysis mode",
	Long:  `Start interactive mode to explore and analyze disk usage.`,
	Args:  cobra.MaximumNArgs(1),
	Run:   runAnalyze,
}

func init() {
	rootCmd.AddCommand(analyzeCmd)
}

func runAnalyze(cmd *cobra.Command, args []string) {
	// Determine path to scan
	path := "."
	if len(args) > 0 {
		path = args[0]
	}

	// Resolve absolute path
	absPath, err := filepath.Abs(path)
	checkError(err)

	// Create scanner
	fmt.Printf("🔍 Scanning %s...\n", absPath)
	s := scanner.NewScanner(workers)

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

	// Start interactive mode
	interactiveMode(root)
}

func interactiveMode(root *scanner.FileNode) {
	currentNode := root
	reader := bufio.NewReader(os.Stdin)

	for {
		// Display current directory
		fmt.Printf("\n%s=== Current: %s ===%s\n", ui.ColorBold, currentNode.Path, ui.ColorReset)
		fmt.Printf("Size: %s | Files: %d | Dirs: %d\n\n",
			scanner.FormatSize(currentNode.Size),
			currentNode.FileCount,
			currentNode.DirCount)

		// Display children
		if currentNode.IsDir && len(currentNode.Children) > 0 {
			// Sort children by size
			children := make([]*scanner.FileNode, len(currentNode.Children))
			copy(children, currentNode.Children)
			sort.Slice(children, func(i, j int) bool {
				return children[i].Size > children[j].Size
			})

			fmt.Println("Contents:")
			for i, child := range children {
				icon := "📄"
				if child.IsDir {
					icon = "📁"
				}
				percentage := scanner.GetPercentage(child.Size, currentNode.Size)
				color := ui.ColorGreen
				if percentage >= 50 {
					color = ui.ColorRed
				} else if percentage >= 20 {
					color = ui.ColorYellow
				}

				fmt.Printf("%s%2d.%s %s %s%-40s%s %10s %6.1f%%\n",
					ui.ColorCyan, i+1, ui.ColorReset,
					icon,
					color, truncate(child.Name, 40), ui.ColorReset,
					scanner.FormatSize(child.Size),
					percentage)

				if i >= 19 { // Limit display to 20 items
					remaining := len(children) - 20
					if remaining > 0 {
						fmt.Printf("   ... and %d more items\n", remaining)
					}
					break
				}
			}
		}

		// Show menu
		fmt.Printf("\n%sCommands:%s\n", ui.ColorBold, ui.ColorReset)
		fmt.Println("  [number]  - Enter directory")
		fmt.Println("  u         - Go up one level")
		fmt.Println("  t         - Show top 10 largest items")
		fmt.Println("  c         - Show chart")
		fmt.Println("  f         - Find largest files globally")
		fmt.Println("  h         - Go to home/root")
		fmt.Println("  q         - Quit")
		fmt.Printf("\n%s>%s ", ui.ColorCyan, ui.ColorReset)

		// Read command
		input, err := reader.ReadString('\n')
		if err != nil {
			continue
		}
		input = strings.TrimSpace(input)

		// Process command
		switch input {
		case "q", "quit", "exit":
			fmt.Println("\nGoodbye! 👋")
			return

		case "u", "up", "..":
			if currentNode.Path != root.Path {
				// Find parent
				parent := findParent(root, currentNode)
				if parent != nil {
					currentNode = parent
				} else {
					fmt.Println("Already at root")
				}
			} else {
				fmt.Println("Already at root")
			}

		case "h", "home", "root":
			currentNode = root

		case "t", "top":
			ui.DisplayTopDirs(currentNode, 10)
			ui.DisplayTopFiles(currentNode, 10)

		case "c", "chart":
			ui.DisplayBarChart(currentNode, 20)

		case "f", "find":
			fmt.Println("\n=== Top 20 Largest Files ===\n")
			files := root.FindLargestFiles(20)
			for i, file := range files {
				percentage := scanner.GetPercentage(file.Size, root.Size)
				fmt.Printf("%2d. %s\n    %s (%.2f%%)\n",
					i+1, file.Path, scanner.FormatSize(file.Size), percentage)
			}

		default:
			// Try to parse as number
			num, err := strconv.Atoi(input)
			if err != nil || num < 1 {
				fmt.Printf("%sInvalid command. Try again.%s\n", ui.ColorRed, ui.ColorReset)
				continue
			}

			// Navigate to child
			if currentNode.IsDir && num <= len(currentNode.Children) {
				// Get sorted children
				children := make([]*scanner.FileNode, len(currentNode.Children))
				copy(children, currentNode.Children)
				sort.Slice(children, func(i, j int) bool {
					return children[i].Size > children[j].Size
				})

				child := children[num-1]
				if child.IsDir {
					currentNode = child
				} else {
					// Display file info
					fmt.Printf("\n%s=== File Information ===%s\n", ui.ColorBold, ui.ColorReset)
					fmt.Printf("Name:     %s\n", child.Name)
					fmt.Printf("Path:     %s\n", child.Path)
					fmt.Printf("Size:     %s\n", scanner.FormatSize(child.Size))
					fmt.Printf("Modified: %s\n", child.LastMod.Format("2006-01-02 15:04:05"))
					fmt.Printf("Percent:  %.2f%% of total\n", scanner.GetPercentage(child.Size, root.Size))
				}
			} else {
				fmt.Printf("%sInvalid selection%s\n", ui.ColorRed, ui.ColorReset)
			}
		}
	}
}

// findParent finds the parent node of a given node
func findParent(root, target *scanner.FileNode) *scanner.FileNode {
	if root == target {
		return nil
	}

	var parent *scanner.FileNode
	root.WalkTree(func(node *scanner.FileNode) error {
		if node.IsDir {
			for _, child := range node.Children {
				if child == target {
					parent = node
					return filepath.SkipDir
				}
			}
		}
		return nil
	})
	return parent
}

// truncate truncates a string to maxLen
func truncate(s string, maxLen int) string {
	if len(s) <= maxLen {
		return s
	}
	return s[:maxLen-3] + "..."
}
