import pandas as pd
import matplotlib.pyplot as plt
from sys import argv


def main():
    path = argv[1]
    df = pd.read_csv(path, skiprows=2, names=['accuracy'])

    plt.plot(df['accuracy'])
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy')
    plt.show()



if __name__ == '__main__':
    main()
