/**
 * @file AlgorithmX.hpp
 * @brief Implementation of Algorithm X (Dancing Links) for solving exact cover problems.
 * @author [Your Name]
 */

#include <iostream>
#include <vector>

/**
 * @namespace AlgorithmX
 * @brief A namespace for the Algorithm X (Dancing Links) implementation.
 */
namespace AlgorithmX {

    /**
     * @struct Node
     * @brief A struct representing a node in the dancing links data structure.
     */
    struct Node {
        Node* left;
        Node* right;
        Node* up;
        Node* down;
        Node* column;
        int size;
        int row;
    };

    /**
     * @class ExactCoverSolver
     * @brief A class for solving exact cover problems using Algorithm X.
     */
    class ExactCoverSolver {
    public:
        /**
         * @brief Constructor for ExactCoverSolver.
         * @param numColumns The number of columns in the matrix.
         */
        ExactCoverSolver(int numColumns);

        /**
         * @brief Destructor for ExactCoverSolver.
         */
        ~ExactCoverSolver();

        /**
         * @brief Add a row to the exact cover problem matrix.
         * @param row The row represented as a vector of column indices.
         */
        void addRow(const std::vector<int>& row);

        /**
         * @brief Solve the exact cover problem and print the solutions.
         */
        void solve();

    private:
        Node* createNode();
        void cover(Node* target);
        void uncover(Node* target);
        bool search(int k);

        int numColumns_;
        Node* root_;
        std::vector<Node*> columns_;
        std::vector<Node*> solution_;
    };

} // namespace AlgorithmX

namespace AlgorithmX {

    ExactCoverSolver::ExactCoverSolver(int numColumns) : numColumns_(numColumns) {
        root_ = createNode();
        columns_.resize(numColumns_);
        for (int i = 0; i < numColumns_; ++i) {
            columns_[i] = createNode();
            columns_[i]->left = root_->left;
            columns_[i]->right = root_;
            root_->left->right = columns_[i];
            root_->left = columns_[i];
            columns_[i]->up = columns_[i];
            columns_[i]->down = columns_[i];
            columns_[i]->column = columns_[i];
        }
    }

    ExactCoverSolver::~ExactCoverSolver() {
        for (Node* column : columns_) {
            Node* current = column->down;
            while (current != column) {
                Node* temp = current;
                current = current->down;
                delete temp;
            }
            delete column;
        }
        delete root_;
    }

    Node* ExactCoverSolver::createNode() {
        return new Node{nullptr, nullptr, nullptr, nullptr, nullptr, -1};
    }

    void ExactCoverSolver::addRow(const std::vector<int>& row) {
        Node* first = nullptr;
        for (int col : row) {
            Node* newNode = createNode();
            newNode->row = solution_.size();
            newNode->column = columns_[col];
            columns_[col]->up->down = newNode;
            newNode->up = columns_[col]->up;
            newNode->down = columns_[col];
            columns_[col]->up = newNode;
            if (!first) first = newNode;
        }
        if (first) {
            first->left = solution_.back();
            first->right = solution_.back()->right;
            solution_.back()->right->left = first;
            solution_.back()->right = first;
        }
        solution_.push_back(first);
    }

    void ExactCoverSolver::cover(Node* target) {
        target->right->left = target->left;
        target->left->right = target->right;
        Node* current = target->down;
        while (current != target) {
            Node* rowNode = current;
            Node* rightNode = rowNode->right;
            while (rightNode != rowNode) {
                rightNode->down->up = rightNode->up;
                rightNode->up->down = rightNode->down;
                rightNode->column->size--;
                rightNode = rightNode->right;
            }
            current = current->down;
        }
    }

    void ExactCoverSolver::uncover(Node* target) {
        Node* current = target->up;
        while (current != target) {
            Node* rowNode = current;
            Node* leftNode = rowNode->left;
            while (leftNode != rowNode) {
                leftNode->down->up = leftNode;
                leftNode->up->down = leftNode;
                leftNode->column->size++;
                leftNode = leftNode->left;
            }
            current = current->up;
        }
        target->right->left = target;
        target->left->right = target;
    }

    bool ExactCoverSolver::search(int k) {
        if (root_->right == root_) {
            // Solution found, print it
            std::cout << "Solution: ";
            for (Node* node : solution_) {
                std::cout << node->row << " ";
            }
            std::cout << std::endl;
            return true;
        }

        Node* column = root_->right;
        cover(column);

        Node* current = column->down;
        while (current != column) {
            solution_.push_back(current);

            Node* rightNode = current->right;
            while (rightNode != current) {
                cover(rightNode->column);
                rightNode = rightNode->right;
            }

            if (search(k + 1)) return true;

            rightNode = current->left;
            while (rightNode != current) {
                uncover(rightNode->column);
                rightNode = rightNode->left;
            }

            solution_.pop_back();
            current = current->down;
        }

        uncover(column);
        return false;
    }

    void ExactCoverSolver::solve() {
        if (!search(0)) {
            std::cout << "No solution found." << std::endl;
        }
    }

} // namespace AlgorithmX

int main() {
    AlgorithmX::ExactCoverSolver solver(7); // Assuming 7 columns
    solver.addRow({0, 3, 6});
    solver.addRow({0, 3});
    solver.addRow({3, 4, 6});
    solver.addRow({2, 4});
    solver.addRow({1, 5});
    solver.addRow({2, 5, 7});

    std::cout << "Solving the exact cover problem..." << std::endl;
    solver.solve();
    std::cout << "Solving complete." << std::endl;

    return 0;
}
