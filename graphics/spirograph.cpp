/**
 * @file
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief Implementation of
 * [Spirograph](https://en.wikipedia.org/wiki/Spirograph)
 *
 * @details
 * Implementation of the program is based on the geometry shown in the figure
 * below:
 *
 * <a
 * href="https://commons.wikimedia.org/wiki/File:Resonance_Cascade.svg"><img
 * src="https://upload.wikimedia.org/wikipedia/commons/3/39/Resonance_Cascade.svg"
 * alt="Spirograph geometry from Wikipedia" style="width: 250px"/></a>
 */
#define _USE_MATH_DEFINES /**< required for MSVC compiler */
#include <array>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#ifdef _OPENMP
#include <omp.h>
#endif

/**
 * @namespace spirograph Functions related to spirograph.c
 */
namespace spirograph {
/** Generate spirograph curve into arrays `x` and `y` such that the i^th point
 * in 2D is represented by `(x[i],y[i])`. The generating function is given by:
 * \f{eqnarray*}{
 * x &=& R\left[ (1-k) \cos (t) + l\cdot k\cdot\cos \left(\frac{1-k}{k}t\right)
 * \right]\\
 * y &=& R\left[ (1-k) \sin (t) - l\cdot k\cdot\sin \left(\frac{1-k}{k}t\right)
 * \right] \f}
 * where
 * * \f$R\f$ is the scaling parameter that we will consider \f$=1\f$
 * * \f$l=\frac{\rho}{r}\f$ is the relative distance of marker from the centre
 * of inner circle and \f$0\le l\le1\f$
 * * \f$\rho\f$ is physical distance of marker from centre of inner circle
 * * \f$r\f$ is the radius of inner circle
 * * \f$k=\frac{r}{R}\f$ is the ratio of radius of inner circle to outer circle
 * and \f$0<k<1\f$
 * * \f$R\f$ is the radius of outer circle
 * * \f$t\f$ is the angle of rotation of the point i.e., represents the time
 * parameter
 *
 * Since we are considering ratios, the actual values of \f$r\f$ and
 * \f$R\f$ are immaterial.
 *
 * @tparam N number of points = size of array
 * @param [out] points Array of 2D points represented as std::pair
 * @param l the relative distance of marker from the centre of
 * inner circle and \f$0\le l\le1\f$
 * @param k the ratio of radius of inner circle to outer circle and \f$0<k<1\f$
 * @param rot the number of rotations to perform (can be fractional value)
 */
template <std::size_t N>
void spirograph(std::array<std::pair<double, double>, N> *points, double l,
                double k, double rot) {
    double dt = rot * 2.f * M_PI / N;
    double R = 1.f;
    const double k1 = 1.f - k;
    int32_t step;

#ifdef _OPENMP
#pragma omp for
#endif
    for (step = 0; step < N; step++) {
        double t = dt * step;
        points[0][step].first = R * (k1 * cos(t) + l * k * cos(k1 * t / k));
        points[0][step].second = R * (k1 * sin(t) - l * k * sin(k1 * t / k));
    }
}

/**
 * @brief Test function to save resulting points to a CSV file.
 *
 */
void test() {
    const size_t N = 500;
    double l = 0.3, k = 0.75, rot = 10.;
    std::stringstream fname;
    fname << std::setw(3) << "spirograph_" << l << "_" << k << "_" << rot
          << ".csv";
    std::ofstream fp(fname.str());
    if (!fp.is_open()) {
        perror(fname.str().c_str());
        exit(EXIT_FAILURE);
    }

    std::array<std::pair<double, double>, N> points;

    spirograph(&points, l, k, rot);

    for (size_t i = 0; i < N; i++) {
        fp << points[i].first << "," << points[i].first;
        if (i < N - 1) {
            fp << '\n';
        }
    }

    fp.close();
}

#ifdef GLUT_FOUND  // this is set by CMAKE automatically, if available
#ifdef __APPLE__
#include <GLUT/glut.h>  // include path on Macs is different
#else
#include <GL/glut.h>
#endif

/** A wrapper that is not available in all GLUT implementations.
 */
static inline void glutBitmapString(void *font, char *message) {
    for (char *ch = message; *ch != '\0'; ch++) glutBitmapCharacter(font, *ch);
}

/**
 * @brief Function to graph (x,y) points on the OpenGL graphics window.
 *
 * @tparam N number of points = size of array
 * @param [in] points Array of 2D points represented as std::pair
 * @param l the relative distance of marker from the centre of
 * inner circle and \f$0\le l\le1\f$ to display info
 * @param k the ratio of radius of inner circle to outer circle and \f$0<k<1\f$
 * to display info
 */
template <size_t N>
void display_graph(const std::array<std::pair<double, double>, N> &points,
                   double l, double k) {
    glClearColor(1.0f, 1.0f, 1.0f,
                 0.0f);            // Set background color to white and opaque
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer (background)

    glBegin(GL_LINES);         // draw line segments
    glColor3f(0.f, 0.f, 1.f);  // blue
    glPointSize(2.f);          // point size in pixels

    for (size_t i = 1; i < N; i++) {
        glVertex2f(points[i - 1].first, points[i - 1].second);  // line from
        glVertex2f(points[i].first, points[i].second);          // line to
    }
    glEnd();

    glColor3f(0.f, 0.f, 0.f);
    std::stringstream buffer;
    buffer << std::setw(3) << "l = " << l;
    glRasterPos2f(-.85, .85);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,
                     const_cast<char *>(buffer.str().c_str()));
    buffer.str("");
    buffer.clear();
    buffer << std::setw(3) << "k = " << k;
    glRasterPos2f(-.85, .70);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,
                     const_cast<char *>(buffer.str().c_str()));

    glutSwapBuffers();
}

/**
 * @brief Test function with animation
 *
 */
void test2() {
    const size_t N = 5000;     // number of samples
    const double step = 0.01;  // animation steps
    static double l = step * 10, k = step, rot = 20.;

    static bool direction1 = true;  // increment if true, otherwise decrement
    static bool direction2 = true;  // increment if true, otherwise decrement

    std::array<std::pair<double, double>, N> points;

    spirograph(&points, l, k, rot);
    display_graph(points, l, k);

    if (direction1) {            // increment k
        if (k >= (1.f - step))   // maximum limit
            direction1 = false;  // reverse direction of k
        else
            k += step;
    } else {                    // decrement k
        if (k <= step) {        // minimum limit
            direction1 = true;  // reverse direction of k

            if (direction2) {            // increment l
                if (l >= (1.f - step))   // max limit of l
                    direction2 = false;  // reverse direction of l
                else
                    l += step;
            } else {                    // decrement l
                if (l <= step)          // minimum limit of l
                    direction2 = true;  // reverse direction of l
                else
                    l -= step;
            }
        } else {  // no min limit of k
            k -= step;
        }
    }
}

/**
 * @brief GLUT timer callback function to add animation delay.
 */
void timer_cb(int t) {
    glutTimerFunc(25, timer_cb, 0);
    glutPostRedisplay();
}
#endif
}  // namespace spirograph

/** Main function */
int main(int argc, char **argv) {
#ifdef GLUT_FOUND
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Spirograph");
    glutInitWindowSize(400, 400);
    // glutIdleFunc(glutPostRedisplay);
    glutTimerFunc(25, spirograph::timer_cb, 0);
    glutDisplayFunc(spirograph::test2);
    glutMainLoop();
#else
    spirograph::test();
#endif

    return 0;
}
