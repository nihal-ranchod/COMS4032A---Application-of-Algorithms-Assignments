import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

data_a1 = pd.read_csv('Assignment 3/part_A_1_averaged.csv')
data_a2 = pd.read_csv('Assignment 3/part_A_2_averaged.csv')

# A-1: Average Execution Time vs Number of Elements
plt.figure(figsize=(12, 6))
sns.lineplot(data=data_a1, x='Number of elements', y='Average Execution time', color='seagreen')
plt.title('Average Execution Time vs Number of Elements for Part A-1')
plt.xlabel('Number of Elements')
plt.ylabel('Average Execution Time (s)')
plt.grid(True)
plt.savefig('Assignment 3/Graphs/Part A-1/average_execution_time.png')
plt.show()

# A-1: Average Find-Set Count vs Number of Elements
plt.figure(figsize=(12, 6))
sns.lineplot(data=data_a1, x='Number of elements', y='Average FIND_SET Count', color='red', label='Average Find-Set Count')
plt.title('Average Find-Set Count vs Number of Elements for Part A-1')
plt.xlabel('Number of Elements')
plt.ylabel('Average Count')
plt.legend(title='Count')
plt.grid(True)
plt.savefig('Assignment 3/Graphs/Part A-1/average_find_set_count.png')
plt.show()

# A-2: Average Execution Time vs Number of Elements
plt.figure(figsize=(12, 6))
sns.lineplot(data=data_a2, x='Number of elements', y='Average Execution time', color='purple')
plt.title('Average Execution Time vs Number of Elements for Part A-2')
plt.xlabel('Number of Elements')
plt.ylabel('Average Execution Time (s)')
plt.grid(True)
plt.savefig('Assignment 3/Graphs/Part A-2/average_execution_time.png')
plt.show()

# A-2: Average Find-Set Count vs Number of Elements
plt.figure(figsize=(12, 6))
sns.lineplot(data=data_a2, x='Number of elements', y='Average FIND_SET Count', color='red', label='Average Find-Set Count')
plt.title('Average  Find-Set Count vs Number of Elements for Part A-2')
plt.xlabel('Number of Elements')
plt.ylabel('Average Count')
plt.legend(title='Count')
plt.grid(True)
plt.savefig('Assignment 3/Graphs/Part A-2/average_find_set_count.png')
plt.show()

# Combined: Average Execution Time vs Number of Elements
plt.figure(figsize=(12, 6))
sns.lineplot(data=data_a1, x='Number of elements', y='Average Execution time', color='seagreen', label='Part A-1')
sns.lineplot(data=data_a2, x='Number of elements', y='Average Execution time', color='purple', label='Part A-2')
plt.title('Average Execution Time vs Number of Elements')
plt.xlabel('Number of Elements')
plt.ylabel('Average Execution Time (s)')
plt.legend(title='Part')
plt.grid(True)
plt.savefig('Assignment 3/Graphs/Analysis/average_execution_time.png')
plt.show()

# Combined: Average Find-Set Count vs Number of Elements
plt.figure(figsize=(12, 6))

sns.lineplot(data=data_a1, x='Number of elements', y='Average FIND_SET Count', color='red', label='Average Find-Set Count (Part A-1)')
sns.lineplot(data=data_a2, x='Number of elements', y='Average FIND_SET Count', color='blue', label='Average Find-Set Count (Part A-2)')
plt.title('Average Find-Set Count vs Number of Elements')
plt.xlabel('Number of Elements')
plt.ylabel('Average Count')
plt.legend(title='Count')
plt.grid(True)
plt.savefig('Assignment 3/Graphs/Analysis/average_find_set_count.png')
plt.show()


