import csv
import matplotlib.pyplot as plt

h = []
ti = []
tr = []
te = []
with open('./logs.csv', 'r') as file:
    reader = csv.reader(file)
    print(reader)
    i = 0
    for row in reader:
        h.append(i)
        ti.append(float(row[1]))
        te.append(float(row[2])  )
        tr.append(float(row[3]))
        i += 1

plt.plot(h, ti, color='green')
plt.plot(h, tr, color='red')
plt.plot(h, te, color='blue')

plt.show()