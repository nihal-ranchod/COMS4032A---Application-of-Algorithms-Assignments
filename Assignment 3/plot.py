import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

data = pd.read_csv('Assignment 3/disjoint_set_average_results.csv')
# print(data)

# Average Execution Time vs Number of Elements for Basic Union
plt.figure(figsize=(12, 6))
sns.lineplot(data=data, x='Number of elements', y='Average Union Execution time', color='seagreen')
plt.title('Average Union Execution Time vs Number of Elements')
plt.xlabel('Number of Elements')
plt.ylabel('Average Union Execution Time (s)')
plt.grid(True)
plt.savefig('Assignment 3/Graphs/average_union_execution_time.png')
plt.show()

# Average Weighted-Union Execution Time vs Number of Elements
plt.figure(figsize=(12, 6))
sns.lineplot(data=data, x='Number of elements', y='Average Weighted Union Execution time', color='purple')
plt.title('Average Weighted-Union Execution Time vs Number of Elements')
plt.xlabel('Number of Elements')
plt.ylabel('Average Weighted-Union Execution Time (s)')
plt.grid(True)
plt.savefig('Assignment 3/Graphs/average_weighted_union_execution_time.png')
plt.show()

# Average Union-by-Rank Execution Time vs Number of Elements
plt.figure(figsize=(12, 6))
sns.lineplot(data=data, x='Number of elements', y='Average Union-by-Rank Execution time', color='blue')
plt.title('Average Union-by-Rank Execution Time vs Number of Elements')
plt.xlabel('Number of Elements')
plt.ylabel('Average Union-by-Rank Execution Time (s)')
plt.grid(True)
plt.savefig('Assignment 3/Graphs/average_union_by_rank_execution_time.png')
plt.show()


# Combined: Average Execution Time vs Number of Elements
plt.figure(figsize=(12, 6))
sns.lineplot(data=data, x='Number of elements', y='Average Union Execution time', color='seagreen', label='Union')
sns.lineplot(data=data, x='Number of elements', y='Average Weighted Union Execution time', color='purple', label='Weighted Union')
sns.lineplot(data=data, x='Number of elements', y='Average Union-by-Rank Execution time', color='blue', label='Union by Rank')
plt.title('Average Execution Time vs Number of Elements')
plt.xlabel('Number of Elements')
plt.ylabel('Average Execution Time (s)')
plt.legend(title='Method')
plt.grid(True)
plt.savefig('Assignment 3/Graphs/average_execution_time.png')
plt.show()
