/**
 * @file k_means_clustering.cpp
 * @brief K Means Clustering Algorithm implemented
 * @details
 * This file has K Means algorithm implemmented
 * It prints test output in eps format
 * @author [Lakhan Nad](https://github.com/Lakhan-Nad)
 */

#include <cmath>    // PI
#include <cstdio>   // printf
#include <cstdlib>  // for rand

/*! \class observation
 *  a class to store points in 2d plane
 *  the name observation is used to denote
 *  a random point in plane
 */
class observation {
 public:
  double x, y;
  size_t group;
  observation() {
    x = 0.0, y = 0.0;
    group = 0;
  }
  observation(double xx, double yy) {
    x = xx;
    y = yy;
  }
};

/*! \class cluster
 *  this class stores the coordinates
 *  of centroid of all the points
 *  in that cluster it also
 *  stores the count of observations
 *  belonging to this cluster
 */

class cluster {
 public:
  double x, y;
  size_t count;
  cluster() {
    x = 0.0, y = 0.0;
    count = 0;
  }
};

/*! \fn printEPS
 * A function to print observations and clusters
 * The code is taken from
 * @link http://rosettacode.org/wiki/K-means%2B%2B_clustering
 * its C implementation
 * Even the K Means code is also inspired from it
 *
 * to print in a file use pipeline operator ( ./a.out > image.eps )
 *
 * @param observations - observations array
 * @param len - size of observation array
 * @param cent - clusters centroid's array
 * @param k - size of cent array
 */
void printEPS(observation pts[], size_t len, cluster cent[], int k) {
  int W = 400, H = 400;
  double min_x, max_x, min_y, max_y, scale, cx, cy;
  double* colors = new double[k * 3];

  for (int i = 0; i < k; i++) {
    colors[3 * i + 0] = (3 * (i + 1) % 11) / 11.;
    colors[3 * i + 1] = (7 * i % 11) / 11.;
    colors[3 * i + 2] = (9 * i % 11) / 11.;
  }

  max_x = max_y = -(min_x = min_y = __DBL_MAX__);
  for (size_t i = 0; i < len; i++) {
    if (max_x < pts[i].x) max_x = pts[i].x;
    if (min_x > pts[i].x) min_x = pts[i].x;
    if (max_y < pts[i].y) max_y = pts[i].y;
    if (min_y > pts[i].y) min_y = pts[i].y;
  }
  scale = W / (max_x - min_x);
  if (scale > H / (max_y - min_y)) scale = H / (max_y - min_y);
  cx = (max_x + min_x) / 2;
  cy = (max_y + min_y) / 2;

  std::printf("%%!PS-Adobe-3.0\n%%%%BoundingBox: -5 -5 %d %d\n", W + 10,
              H + 10);
  std::printf(
      "/l {rlineto} def /m {rmoveto} def\n"
      "/c { .25 sub exch .25 sub exch .5 0 360 arc fill } def\n"
      "/s { moveto -2 0 m 2 2 l 2 -2 l -2 -2 l closepath "
      "	gsave 1 setgray fill grestore gsave 3 setlinewidth"
      " 1 setgray stroke grestore 0 setgray stroke }def\n");
  for (int i = 0; i < k; i++) {
    std::printf("%g %g %g setrgbcolor\n", colors[3 * i], colors[3 * i + 1],
                colors[3 * i + 2]);
    for (size_t j = 0; j < len; j++) {
      if (pts[j].group != i) continue;
      std::printf("%.3f %.3f c\n", (pts[j].x - cx) * scale + W / 2,
                  (pts[j].y - cy) * scale + H / 2);
    }
    std::printf("\n0 setgray %g %g s\n", (cent[i].x - cx) * scale + W / 2,
                (cent[i].y - cy) * scale + H / 2);
  }
  std::printf("\n%%%%EOF");
  delete colors;
}

/*! \fn calculateNearest
 * Returns the index of centroid nearest to
 * given observation
 *
 * @param o - observation
 * @param clusters - array of cluster having centroids coordinates
 * @param k - size of clusters array
 */
int calculateNearst(observation o, cluster clusters[], int k) {
  double minD = __DBL_MAX__;
  double dist;
  int index;
  for (int i = 0; i < k; i++) {
    /* Calculate Squared Distance*/
    dist = (clusters[i].x - o.x) * (clusters[i].x - o.x) +
           (clusters[i].y - o.y) * (clusters[i].y - o.y);
    if (dist < minD) {
      minD = dist;
      index = i;
    }
  }
  return index;
}

/*! \fn calculateCentroid
 * Calculate centoid and assign it to the cluster variable
 *
 * @param observations - an array of observations whose centroid is calculated
 * @param size - size of the observations array
 * @param centroid - a reference to cluster object to store information of
 * centroid
 */
void calculateCentroid(observation observations[], size_t size,
                       cluster& centroid) {
  centroid.x = 0;
  centroid.y = 0;
  centroid.count = size;
  for (int i = 0; i < size; i++) {
    centroid.x += observations[i].x;
    centroid.y += observations[i].y;
  }
  centroid.x /= centroid.count;
  centroid.y /= centroid.count;
}

/*!  \fn kMeans
 *   --K Means Algorithm--
 * 1. Assign each observation to one of k groups
 *    creating a random initial clustering
 * 2. Find the centroid of observations for each
 *    cluster to form new centroids
 * 3. Find the centroid which is nearest for each
 *    observation among the calculated centroids
 * 4. Assign the observation to its nearest centroid
 *    to create a new clustering.
 * 5. Repeat step 2,3,4 until there is no change
 *    the current clustering and is same as last
 *    clustering.
 * @param observations - an array of observations to cluster
 * @param size - size of observations array
 * @param k - no of clusters to be made
 *
 * @returns void
 */
cluster* kMeans(observation observations[], size_t size, int k) {
  k = k < 1 ? 1 : k;
  cluster* clusters = new cluster[k];
  if (k == 1) {
    /*
    If we have to cluster them only in one group
    then calculate centroid of observations
    */
    calculateCentroid(observations, size, clusters[0]);
  } else if (k >= size) {
    /* If no of clusters is more than observations
       each observation can be its own cluster
    */
    for (size_t i = 0; i < size; i++) {
      clusters[i].x = observations[i].x;
      clusters[i].y = observations[i].y;
      clusters[i].count = 0;
    }
  } else {
    /* STEP 1 */
    for (size_t i = 0; i < size; i++) {
      observations[i].group = std::rand() % k;
    }
    size_t changed;
    size_t minAcceptedError =
        size / 10000;  // Do until 99.99 percent points are in correct cluster
    int t;
    do {
      /* Initialize clusters */
      for (int i = 0; i < k; i++) {
        clusters[i].x = 0;
        clusters[i].y = 0;
        clusters[i].count = 0;
      }
      /* STEP 2*/
      for (size_t i = 0; i < size; i++) {
        t = observations[i].group;
        clusters[t].x += observations[i].x;
        clusters[t].y += observations[i].y;
        clusters[t].count++;
      }
      for (int i = 0; i < k; i++) {
        clusters[i].x /= clusters[i].count;
        clusters[i].y /= clusters[i].count;
      }
      /* STEP 3 and 4 */
      changed = 0;  // this variable stores change in clustering
      for (size_t i = 0; i < size; i++) {
        t = calculateNearst(observations[i], clusters, k);
        if (t != observations[i].group) {
          changed++;
          observations[i].group = t;
        }
      }
    } while (changed > minAcceptedError);  // Keep on grouping until we have got
                                           // almost best clustering
  }
  return clusters;
}

/*! \fn test
 * A function to test the kMeans function
 * Generates 100000 points in square
 * (0,0),(10,0),(10,10),(0,10)
 * and cluster them into 10 clusters
 */
void test() {
  size_t size = 1000000L;
  observation* observations = new observation[size];
  double maxRadius = 20.00;
  double radius;
  double ang;
  for (size_t i = 0; i < size; i++) {
    radius = (maxRadius * std::rand()) / RAND_MAX;
    ang = (2 * M_PI * std::rand()) / RAND_MAX;
    observations[i].x = radius * std::cos(ang);
    observations[i].y = radius * std::sin(ang);
  }
  int k = 20;  // No of clusters
  cluster* clusters = kMeans(observations, size, k);
  printEPS(observations, size, clusters, k);
  delete observations;
  delete clusters
}

int main() {
  test();
  return 0;
}