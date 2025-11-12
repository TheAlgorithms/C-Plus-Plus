.PHONY: build install clean test run help

# Variables
BINARY_NAME=diskscan
GO=go
GOFLAGS=-ldflags="-s -w"
INSTALL_PATH=/usr/local/bin

# Default target
all: build

# Build the binary
build:
	@echo "Building $(BINARY_NAME)..."
	$(GO) build $(GOFLAGS) -o $(BINARY_NAME)
	@echo "Build complete!"

# Build with race detector (for development)
build-dev:
	@echo "Building $(BINARY_NAME) with race detector..."
	$(GO) build -race -o $(BINARY_NAME)
	@echo "Build complete!"

# Install the binary
install: build
	@echo "Installing $(BINARY_NAME) to $(INSTALL_PATH)..."
	sudo cp $(BINARY_NAME) $(INSTALL_PATH)/
	@echo "Installation complete!"

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -f $(BINARY_NAME)
	$(GO) clean
	@echo "Clean complete!"

# Run tests
test:
	@echo "Running tests..."
	$(GO) test -v ./...

# Run tests with coverage
test-coverage:
	@echo "Running tests with coverage..."
	$(GO) test -cover -coverprofile=coverage.out ./...
	$(GO) tool cover -html=coverage.out -o coverage.html
	@echo "Coverage report generated: coverage.html"

# Run the application
run: build
	./$(BINARY_NAME)

# Cross-compile for multiple platforms
build-all:
	@echo "Building for multiple platforms..."
	GOOS=linux GOARCH=amd64 $(GO) build $(GOFLAGS) -o dist/$(BINARY_NAME)-linux-amd64
	GOOS=linux GOARCH=arm64 $(GO) build $(GOFLAGS) -o dist/$(BINARY_NAME)-linux-arm64
	GOOS=darwin GOARCH=amd64 $(GO) build $(GOFLAGS) -o dist/$(BINARY_NAME)-darwin-amd64
	GOOS=darwin GOARCH=arm64 $(GO) build $(GOFLAGS) -o dist/$(BINARY_NAME)-darwin-arm64
	GOOS=windows GOARCH=amd64 $(GO) build $(GOFLAGS) -o dist/$(BINARY_NAME)-windows-amd64.exe
	@echo "Cross-compilation complete! Binaries in dist/"

# Format code
fmt:
	@echo "Formatting code..."
	$(GO) fmt ./...
	@echo "Format complete!"

# Run linter
lint:
	@echo "Running linter..."
	golangci-lint run ./...

# Show help
help:
	@echo "Available targets:"
	@echo "  build         - Build the binary"
	@echo "  build-dev     - Build with race detector"
	@echo "  install       - Install binary to $(INSTALL_PATH)"
	@echo "  clean         - Remove build artifacts"
	@echo "  test          - Run tests"
	@echo "  test-coverage - Run tests with coverage report"
	@echo "  run           - Build and run the application"
	@echo "  build-all     - Cross-compile for all platforms"
	@echo "  fmt           - Format code"
	@echo "  lint          - Run linter"
	@echo "  help          - Show this help message"
