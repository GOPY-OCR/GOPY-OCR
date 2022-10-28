import matplotlib.pyplot as plt
import pandas as pd
from sys import argv

def main():
    if len(argv) != 2:
        print("Usage: display_xor_outputs.py <path_to_xor_outputs.csv>")
        exit(1)

    df = pd.read_csv(argv[1], skiprows=2, names=["x1", "x2", "y"], sep=";")
    print(df)

    df_size = len(df)

    N = int(df_size ** 0.5)

    image = df["y"].values.reshape(N, N)
    xs = df["x1"].values.reshape(N, N)
    ys = df["x2"].values.reshape(N, N)

    # draws a square of size 1 at 0, 0
    plt.plot([0, 1, 1, 0, 0], [0, 0, 1, 1, 0], color="red")

    plt.imshow(image, extent=[df["x1"][0], df["x1"][df_size-1], df["x2"][0], df["x2"][df_size-1]], cmap="gray")
    plt.show()


if __name__ == "__main__":
    main()
