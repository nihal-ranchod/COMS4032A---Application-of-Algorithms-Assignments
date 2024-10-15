import pandas as pd
import matplotlib.pyplot as plt

# Step 1: Read the CSV file
df = pd.read_csv('Assignment 3/disjoint_set_average_results.csv')

union_time = df['Average Union Execution time']
weighted_union_time = df['Average Weighted Union Execution time']
union_by_rank_time = df['Average Union-by-Rank Execution time']

weighted_union_percentage = ((union_time - weighted_union_time) / union_time) * 100
union_by_rank_percentage = ((union_time - union_by_rank_time) / union_time) * 100


implementations = ['Weighted Union', 'Union-by-Rank']
percentages = [weighted_union_percentage.iloc[-1], union_by_rank_percentage.iloc[-1]]

plt.figure(figsize=(10, 6))
bars = plt.bar(implementations, percentages, color=['green', 'blue'])

for bar in bars:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2, yval, f'{round(yval, 2)}%', ha='center', va='bottom')

plt.xlabel('Implementation')
plt.ylabel('Percentage Faster than Union (%)')
plt.title('Percentage Improvement of Weighted Union and Union-by-Rank over Union')
plt.savefig('Assignment 3/Graphs/percentage_improvement.png')
plt.show()