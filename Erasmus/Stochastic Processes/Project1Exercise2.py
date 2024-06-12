import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

# Define the dynamic system function
def dynamic_system(x):
    return 4 * x * (1 - x)

# Simulate the trajectory for a given number of iterations
def simulate_trajectory(x0, iterations):
    trajectory = [x0]
    for _ in range(iterations):
        x0 = dynamic_system(x0)
        trajectory.append(x0)
    return np.array(trajectory)

# Function to plot histograms of trajectory sections
def plot_trajectory_histograms(starting_points, iterations, section_lengths):
    for start_point in starting_points:
        trajectory = simulate_trajectory(start_point, iterations)
        for length in section_lengths:
            plt.hist(trajectory[:length], bins=20, alpha=0.5, label=f'Start={start_point}, Length={length}')
        plt.title('Histograms of Trajectory Sections')
        plt.xlabel('x')
        plt.ylabel('Frequency')
        plt.legend()
        plt.show()

# Function to plot density plot of the invariant measure
def plot_invariant_measure_density(starting_points, iterations):
    final_points = []
    for start_point in starting_points:
        trajectory = simulate_trajectory(start_point, iterations)
        final_points.append(trajectory[-1])

    sns.kdeplot(final_points, shade=True)
    plt.title('Density Plot of Invariant Measure')
    plt.xlabel('x')
    plt.ylabel('Density')
    plt.show()

# Function to plot empirical distribution function
def plot_empirical_distribution(starting_points, iterations):
    all_points = []
    for start_point in starting_points:
        trajectory = simulate_trajectory(start_point, iterations)
        all_points.extend(trajectory)

    plt.hist(all_points, bins=50, density=True, cumulative=True, alpha=0.8, histtype='step')
    plt.title('Empirical Distribution Function')
    plt.xlabel('x')
    plt.ylabel('Cumulative Probability')
    plt.show()

# Example usage
starting_points = [0.1, 0.3, 0.6]
iterations = 1000
section_lengths = [50, 100, 200]

plot_trajectory_histograms(starting_points, iterations, section_lengths)
plot_invariant_measure_density(starting_points, iterations)
plot_empirical_distribution(starting_points, iterations)

# Exercise 3:
#The histograms reveal a random dispersion of function values across the interval, concentrating notably at its extremes. However, near fixed points, especially with an initial condition of x = 0.5, rapid convergence shifts the pattern, centering the histogram around x = 0. Our Chaos Theory study confirms the function's chaotic nature, elucidating the instability of fixed points. Chaotic systems, inherently sensitive to initial conditions, exhibit divergent trajectories with minor variations, accentuating the inherent instability of fixed points. This sensitivity, coupled with the observation of intricate structures in trajectories and distribution functions, highlights the characteristic behavior of chaotic dynamical systems.