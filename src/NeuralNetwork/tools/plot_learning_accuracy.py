import pandas as pd
import matplotlib.pyplot as plt
from sys import argv


def main():
    path = argv[1]
    df = pd.read_csv(path, names=['test accuracy', 'train accuracy'], sep=";")

    print(df)

    df.plot(kind='line', color=['red', 'blue'], title='Learning accuracy', y=['test accuracy', 'train accuracy'])
    
    plt.show()



if __name__ == '__main__':
    main()
