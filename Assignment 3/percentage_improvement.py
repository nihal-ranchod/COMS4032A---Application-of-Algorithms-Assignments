import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('Assignment 3/disjoint_set_average_results.csv')

union_time = df['Average Union Execution time']
weighted_union_time = df['Average Weighted Union Execution time']
union_by_rank_time = df['Average Union-by-Rank Execution time']

weighted_union_percentage = ((union_time - weighted_union_time) / union_time) * 100
union_by_rank_percentage = ((union_time - union_by_rank_time) / union_time) * 100
union_by_rank_over_weighted_union_percentage = ((weighted_union_time - union_by_rank_time) / weighted_union_time) * 100

implementations = ['Weighted Union over Union', 'Union-by-Rank over Union', 'Union-by-Rank over Weighted Union']
percentages_last = [
    weighted_union_percentage.iloc[-1], 
    union_by_rank_percentage.iloc[-1], 
    union_by_rank_over_weighted_union_percentage.iloc[-1]
]

percentages_small = [
    weighted_union_percentage.iloc[0], 
    union_by_rank_percentage.iloc[0], 
    union_by_rank_over_weighted_union_percentage.iloc[0]
]

plt.figure(figsize=(10, 6))
bars = plt.bar(implementations, percentages_small, color=['seagreen', 'darkblue', 'coral'])

for bar in bars:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2, yval, f'{round(yval, 2)}%', ha='center', va='bottom')

plt.ylabel('Percentage Faster (%)')
plt.title('Percentage Improvement of Weighted Union and Union-by-Rank Operations for small n (n = 100)')
plt.savefig('Assignment 3/Graphs/percentage_improvement_small.png')
plt.show()

plt.figure(figsize=(10, 6))
bars = plt.bar(implementations, percentages_last, color=['seagreen', 'darkblue', 'coral'])

for bar in bars:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2, yval, f'{round(yval, 2)}%', ha='center', va='bottom')

plt.ylabel('Percentage Faster (%)')
plt.title('Percentage Improvement of Weighted Union and Union-by-Rank Operations for large n (n = 100000)')
plt.savefig('Assignment 3/Graphs/percentage_improvement_large.png')
plt.show()