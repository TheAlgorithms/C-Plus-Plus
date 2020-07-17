/**
 * \file
 * \authors [Krishna Vedala](https://github.com/kvedala)
 * \brief Solve a multivariable first order [ordinary differential equation
 * (ODEs)](https://en.wikipedia.org/wiki/Ordinary_differential_equation) using
 * [midpoint Euler
 * method](https://en.wikipedia.org/wiki/Midpoint_method)
 *
 * \details
 * The ODE being solved is:
 * \f{eqnarray*}{
 * \dot{u} &=& v\\
 * \dot{v} &=& -\omega^2 u\\
 * \omega &=& 1\\
 * [x_0, u_0, v_0] &=& [0,1,0]\qquad\ldots\text{(initial values)}
 * \f}
 * The exact solution for the above problem is:
 * \f{eqnarray*}{
 * u(x) &=& \cos(x)\\
 * v(x) &=& -\sin(x)\\
 * \f}
 * The computation results are stored to a text file `midpoint_euler.csv` and
 * the exact soltuion results in `exact.csv` for comparison. <img
 * src="https://raw.githubusercontent.com/TheAlgorithms/C-Plus-Plus/docs/images/numerical_methods/ode_midpoint_euler.svg"
 * alt="Implementation solution"/>
 *
 * To implement [Van der Pol
 * oscillator](https://en.wikipedia.org/wiki/Van_der_Pol_oscillator), change the
 * ::problem function to:
 * ```cpp
 * const double mu = 2.0;
 * dy[0] = y[1];
 * dy[1] = mu * (1.f - y[0] * y[0]) * y[1] - y[0];
 * ```
 * \see ode_forward_euler.cpp, ode_semi_implicit_euler.cpp
 */

#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <valarray>

/**
 * @brief Problem statement for a system with first-order differential
 * equations. Updates the system differential variables.
 * \note This function can be updated to and ode of any order.
 *
 * @param[in] 		x 		independent variable(s)
 * @param[in,out]	y		dependent variable(s)
 * @param[in,out]	dy	    first-derivative of dependent variable(s)
 */
void problem(const double &x, std::valarray<double> *y,
             std::valarray<double> *dy) {
    const double omega = 1.F;             // some const for the problem
    dy[0][0] = y[0][1];                   // x dot
    dy[0][1] = -omega * omega * y[0][0];  // y dot
}

/**
 * @brief Exact solution of the problem. Used for solution comparison.
 *
 * @param[in] 		x 		independent variable
 * @param[in,out]	y		dependent variable
 */
void exact_solution(const double &x, std::valarray<double> *y) {
    y[0][0] = std::cos(x);
    y[0][1] = -std::sin(x);
}

/** \addtogroup ode Ordinary Differential Equations
 * @{
 */
/**
 * @brief Compute next step approximation using the midpoint-Euler
 * method.
 * @f[y_{n+1} = y_n + dx\, f\left(x_n+\frac{1}{2}dx,
 * y_n + \frac{1}{2}dx\,f\left(x_n,y_n\right)\right)@f]
 *
 * @param[in] 		dx	step size
 * @param[in] 	    x	take \f$x_n\f$ and compute \f$x_{n+1}\f$
 * @param[in,out] 	y	take \f$y_n\f$ and compute \f$y_{n+1}\f$
 * @param[in,out]	dy	compute \f$f\left(x_n,y_n\right)\f$
 */
void midpoint_euler_step(const double dx, const double &x,
                         std::valarray<double> *y, std::valarray<double> *dy) {
    problem(x, y, dy);
    double tmp_x = x + 0.5 * dx;

    std::valarray<double> tmp_y = y[0] + dy[0] * (0.5 * dx);

    problem(tmp_x, &tmp_y, dy);

    y[0] += dy[0] * dx;
}

/**
 * @brief Compute approximation using the midpoint-Euler
 * method in the given limits.
 * @param[in] 		dx  	step size
 * @param[in]   	x0  	initial value of independent variable
 * @param[in] 	    x_max	final value of independent variable
 * @param[in,out] 	y	    take \f$y_n\f$ and compute \f$y_{n+1}\f$
 * @param[in] save_to_file	flag to save results to a CSV file (1) or not (0)
 * @returns time taken for computation in seconds
 */
double midpoint_euler(double dx, double x0, double x_max,
                      std::valarray<double> *y, bool save_to_file = false) {
    std::valarray<double> dy = y[0];

    std::ofstream fp;
    if (save_to_file) {
        fp.open("midpoint_euler.csv", std::ofstream::out);
        if (!fp.is_open()) {
            std::perror("Error! ");
        }
    }

    std::size_t L = y->size();

    /* start integration */
    std::clock_t t1 = std::clock();
    double x = x0;
    do {  // iterate for each step of independent variable
        if (save_to_file && fp.is_open()) {
            // write to file
            fp << x << ",";
            for (int i = 0; i < L - 1; i++) {
                fp << y[0][i] << ",";
            }
            fp << y[0][L - 1] << "\n";
        }

        midpoint_euler_step(dx, x, y, &dy);  // perform integration
        x += dx;                             // update step
    } while (x <= x_max);  // till upper limit of independent variable
    /* end of integration */
    std::clock_t t2 = std::clock();

    if (fp.is_open())
        fp.close();

    return static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
}

/** @} */

/**
 * Function to compute and save exact solution for comparison
 *
 * \param [in]    X0  	    initial value of independent variable
 * \param [in] 	  X_MAX	    final value of independent variable
 * \param [in] 	  step_size	independent variable step size
 * \param [in]    Y0	    initial values of dependent variables
 */
void save_exact_solution(const double &X0, const double &X_MAX,
                         const double &step_size,
                         const std::valarray<double> &Y0) {
    double x = X0;
    std::valarray<double> y = Y0;

    std::ofstream fp("exact.csv", std::ostream::out);
    if (!fp.is_open()) {
        std::perror("Error! ");
        return;
    }
    std::cout << "Finding exact solution\n";

    std::clock_t t1 = std::clock();
    do {
        fp << x << ",";
        for (int i = 0; i < y.size() - 1; i++) {
            fp << y[i] << ",";
        }
        fp << y[y.size() - 1] << "\n";

        exact_solution(x, &y);

        x += step_size;
    } while (x <= X_MAX);

    std::clock_t t2 = std::clock();
    double total_time = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
    std::cout << "\tTime = " << total_time << " ms\n";

    fp.close();
}

/**
 * Main Function
 */
int main(int argc, char *argv[]) {
    double X0 = 0.f;                       /* initial value of x0 */
    double X_MAX = 10.F;                   /* upper limit of integration */
    std::valarray<double> Y0 = {1.f, 0.f}; /* initial value Y = y(x = x_0) */
    double step_size;

    if (argc == 1) {
        std::cout << "\nEnter the step size: ";
        std::cin >> step_size;
    } else {
        // use commandline argument as independent variable step size
        step_size = std::atof(argv[1]);
    }

    // get approximate solution
    double total_time = midpoint_euler(step_size, X0, X_MAX, &Y0, true);
    std::cout << "\tTime = " << total_time << " ms\n";

    /* compute exact solution for comparion */
    save_exact_solution(X0, X_MAX, step_size, Y0);

    return 0;
}
