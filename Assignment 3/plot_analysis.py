import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Load the data
data_A1 = pd.read_csv('Assignment 3/part_A_1_averaged.csv')
data_A2 = pd.read_csv('Assignment 3/part_A_2_averaged.csv')

# Function to average execution times over union ratios
def average_execution_time(data):
    return data.groupby(['Number of elements', 'Number of operations']).agg({'Average Execution time': 'mean'}).reset_index()

# Average execution times for Part A-1 and Part A-2
avg_data_A1 = average_execution_time(data_A1)
avg_data_A2 = average_execution_time(data_A2)

# Plotting function
def plot_comparison(n):
    plt.figure(figsize=(12, 6))
    sns.lineplot(data=avg_data_A1[avg_data_A1['Number of elements'] == n], x='Number of operations', y='Average Execution time', label='Part A-1', color='green')
    sns.lineplot(data=avg_data_A2[avg_data_A2['Number of elements'] == n], x='Number of operations', y='Average Execution time', label='Part A-2', color='purple')
    plt.title(f'Average Execution Time vs Number of Operations for n = {n}')
    plt.xlabel('Number of Operations')
    plt.ylabel('Average Execution Time (s)')
    plt.legend(title='Part')
    plt.grid(True)
    plt.savefig(f'Assignment 3/Graphs/Analysis/average_execution_time_comparison_n{n}.png')
    plt.show()

# Plot comparisons for different sizes
plot_comparison(1000)
plot_comparison(5000)
plot_comparison(10000)