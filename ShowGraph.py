import matplotlib.pyplot as plt


if __name__ == "__main__":
    f = open("unsorted.txt","r")
    a = f.read()
    values = [int(x) for x in a.split()]
    plt.plot(values)
    f.close()
    f = open("sorted.txt","r")
    a = f.read()
    values = [int(x) for x in a.split()]
    plt.plot(values)
    f.close()
    plt.show()
    