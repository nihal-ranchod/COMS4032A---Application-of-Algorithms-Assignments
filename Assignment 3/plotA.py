import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Part A-1
dataA1 = pd.read_csv('Assignment 3/part_A_1.csv')
print(dataA1)

# Execution Time vs. Number of Operations for Fixed Number of Elements
plt.figure(figsize=(10, 6))
sns.lineplot(x=dataA1['Number of operations'], y=dataA1['Execution time'], color='green')
plt.title('Execution Time vs Number of Operations for Fixed Number of Elements (n = 1000) PART A-1')
plt.xlabel('Number of Operations (m)')
plt.ylabel('Execution Time (seconds)')
plt.grid(True)

plt.savefig('Assignment 3/Graphs/part_A_1.png')
plt.tight_layout()
plt.show()

# Part A-2
dataA2 = pd.read_csv('Assignment 3/part_A_2.csv')
print(dataA2)

# Execution Time vs. Number of Operations for Fixed Number of Elements
plt.figure(figsize=(10, 6))
sns.lineplot(x=dataA2['Number of operations'], y=dataA2['Execution time'], color='purple')
plt.title('Execution Time vs Number of Operations for Fixed Number of Elements (n = 1000) PART A-2')
plt.xlabel('Number of Operations (m)')
plt.ylabel('Execution Time (seconds)')
plt.grid(True)

plt.savefig('Assignment 3/Graphs/part_A_2.png')
plt.tight_layout()
plt.show()

# Combined Plot
plt.figure(figsize=(10, 6))
sns.lineplot(x=dataA1['Number of operations'], y=dataA1['Execution time'], label='Part A-1', color='green')
sns.lineplot(x=dataA2['Number of operations'], y=dataA2['Execution time'], label='Part A-2', color='purple')
plt.title('Execution Time vs Number of Operations for Fixed Number of Elements (n = 1000)')
plt.xlabel('Number of Operations (m)')
plt.ylabel('Execution Time (seconds)')
plt.grid(True)
plt.legend()

plt.savefig('Assignment 3/Graphs/part_A_combined.png')
plt.tight_layout()
plt.show()

