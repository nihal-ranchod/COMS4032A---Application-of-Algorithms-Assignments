import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Part A-1

data = pd.read_csv('Assignment 3/part_A_1_averaged.csv')
# print(f"Data: {data}")

# Execution Times for n = 1000
data_n1 = data[data['Number of elements'] == 1000]
# print(f"Data n1: {data_n1}")

plt.figure(figsize=(12, 6))
sns.lineplot(data=data_n1, x='Number of operations', y='Average Execution time', hue='Union ratio')
plt.title('Average Execution Time vs Number of Operations for n = 1000')
plt.xlabel('Number of Operations')
plt.ylabel('Average Execution Time (s)')
plt.legend(title='Union Ratio')
plt.grid(True)
plt.savefig('Assignment 3/Graphs/Part A-1/average_execution_time_n1000.png')
plt.show()

# Execution Times for n = 5000
data_n2 = data[data['Number of elements'] == 5000]
plt.figure(figsize=(12, 6))
sns.lineplot(data=data_n2, x='Number of operations', y='Average Execution time', hue='Union ratio')
plt.title('Average Execution Time vs Number of Operations for n = 5000')
plt.xlabel('Number of Operations')
plt.ylabel('Average Execution Time (s)')
plt.legend(title='Union Ratio')
plt.grid(True)
plt.savefig('Assignment 3/Graphs/Part A-1/average_execution_time_n5000.png')
plt.show()

# Execution Times for n = 10000
data_n3 = data[data['Number of elements'] == 10000]
plt.figure(figsize=(12, 6))
sns.lineplot(data=data_n3, x='Number of operations', y='Average Execution time', hue='Union ratio')
plt.title('Average Execution Time vs Number of Operations for n = 10000')
plt.xlabel('Number of Operations')
plt.ylabel('Average Execution Time (s)')
plt.legend(title='Union Ratio')
plt.grid(True)
plt.savefig('Assignment 3/Graphs/Part A-1/average_execution_time_n10000.png')
plt.show()

####################################################################################################

# Part A-2

data_A2 = pd.read_csv('Assignment 3/part_A_2_averaged.csv')

data_A2_n1 = data_A2[data_A2['Number of elements'] == 1000]
plt.figure(figsize=(12, 6))
sns.lineplot(data=data_A2_n1, x='Number of operations', y='Average Execution time', hue='Union ratio', palette='crest')
plt.title('Average Execution Time vs Number of Operations for n = 1000')
plt.xlabel('Number of Operations')
plt.ylabel('Average Execution Time (s)')
plt.legend(title='Union Ratio')
plt.grid(True)
plt.savefig('Assignment 3/Graphs/Part A-2/average_execution_time_n1000.png')
plt.show()

data_A2_n2 = data_A2[data_A2['Number of elements'] == 5000]
plt.figure(figsize=(12, 6))
sns.lineplot(data=data_A2_n2, x='Number of operations', y='Average Execution time', hue='Union ratio', palette='crest')
plt.title('Average Execution Time vs Number of Operations for n = 5000')
plt.xlabel('Number of Operations')
plt.ylabel('Average Execution Time (s)')
plt.legend(title='Union Ratio')
plt.grid(True)
plt.savefig('Assignment 3/Graphs/Part A-2/average_execution_time_n5000.png')
plt.show()

data_A2_n3 = data_A2[data_A2['Number of elements'] == 10000]
plt.figure(figsize=(12, 6))
sns.lineplot(data=data_A2_n3, x='Number of operations', y='Average Execution time', hue='Union ratio', palette='crest')
plt.title('Average Execution Time vs Number of Operations for n = 10000')
plt.xlabel('Number of Operations')
plt.ylabel('Average Execution Time (s)')
plt.legend(title='Union Ratio')
plt.grid(True)
plt.savefig('Assignment 3/Graphs/Part A-2/average_execution_time_n10000.png')
plt.show()






