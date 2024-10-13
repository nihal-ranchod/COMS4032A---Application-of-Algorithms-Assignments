import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Load the data
data = pd.read_csv('Assignment 3/part_A_1_averaged.csv')

# Plot Average Execution Time
plt.figure(figsize=(12, 6))
sns.lineplot(data=data, x='Number of operations', y='Average Execution time', hue='Union ratio', marker='o')
plt.title('Average Execution Time vs Number of Operations')
plt.xlabel('Number of Operations')
plt.ylabel('Average Execution Time (s)')
plt.legend(title='Union Ratio')
plt.grid(True)
plt.savefig('average_execution_time.png')
plt.show()

# Plot Average Union Count
plt.figure(figsize=(12, 6))
sns.lineplot(data=data, x='Number of operations', y='Average Union count', hue='Union ratio', marker='o')
plt.title('Average Union Count vs Number of Operations')
plt.xlabel('Number of Operations')
plt.ylabel('Average Union Count')
plt.legend(title='Union Ratio')
plt.grid(True)
plt.savefig('average_union_count.png')
plt.show()

# Plot Average Find-Set Count
plt.figure(figsize=(12, 6))
sns.lineplot(data=data, x='Number of operations', y='Average Find-Set count', hue='Union ratio', marker='o')
plt.title('Average Find-Set Count vs Number of Operations')
plt.xlabel('Number of Operations')
plt.ylabel('Average Find-Set Count')
plt.legend(title='Union Ratio')
plt.grid(True)
plt.savefig('average_find_set_count.png')
plt.show()

# Plot Average Max Depth
plt.figure(figsize=(12, 6))
sns.lineplot(data=data, x='Number of operations', y='Average Max Depth', hue='Union ratio', marker='o')
plt.title('Average Max Depth vs Number of Operations')
plt.xlabel('Number of Operations')
plt.ylabel('Average Max Depth')
plt.legend(title='Union Ratio')
plt.grid(True)
plt.savefig('average_max_depth.png')
plt.show()