import pandas as pd
import matplotlib.pyplot as plt
from sys import argv

def main():
    path = argv[1] if len(argv) > 1 else "_build/accuracies.csv"
    df = pd.read_csv(path, names=['test accuracy', 'train accuracy'], sep=";", skiprows=2)

    df['test accuracy'] = df['test accuracy'].astype(float)

    print(df)

    df.plot(kind='line', color=['red', 'blue'], y=['test accuracy', 'train accuracy'])
    
    plt.show()



if __name__ == '__main__':
    main()
