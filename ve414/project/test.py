import pandas as pd
import numpy as np
import matplotlib as mpl
mpl.use('TkAgg')
import matplotlib.pyplot as plt
from matplotlib.patches import Ellipse, Circle
#data = pd.read_csv("215.csv")
#data = data.sort_values('Close', ascending=True)
import csv
x='[1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 31; 32; 32; 32; 35; 1; 32; 35; 35; 35; 35; 35; 35; 35; 35; 35; 1; 1; 32; 35; 35; 35; 1; 1; 1; 32; 32; 35; 35; 1; 32; 35; 1; 1; 32; 1; 32; 35; 1; 1; 32; 1; 1; 35; 35; 1; 35; 35; 1; 35; 35; 35; 35; 35; 35; 35; 35; 1; 32; 35; 35; 35; 35; 35; 32; 32; 35; 35; 35; 35; 35; 1; 32; 32; 32; 35; 35; 35; 32; 32; 32; 32; 35; 35; 1; 32; 35; 35; 35; 32; 32; 32; 32; 35; 35; 35; 35; 1; 35; 35; 35; 35; 1; 35; 35; 35; 32; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 1; 35; 35; 35; 35; 35; 1; 1; 35; 35; 35; 35; 1; 1; 1; 35; 35; 35; 35; 1; 1; 35; 35; 35; 35; 1; 1; 1; 1; 1; 35; 35; 35; 35; 35; 35; 35; 35; 1; 1; 1; 1; 1; 35; 35; 35; 35; 35; 35; 35; 35; 35; 1; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 1; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 1; 35; 35; 1; 35; 35; 35; 35; 35; 35; 35; 35; 35; 1; 35; 35; 35; 35; 35; 264; 35; 1; 264; 35; 35; 1; 1; 264; 264; 264; 35; 35; 35; 35; 1; 1; 35; 35; 35; 35; 1; 264; 35; 35; 35; 35; 35; 1; 264; 264; 264; 35; 35; 35; 35; 35; 264; 264; 35; 35; 35; 35; 35; 35; 264; 35; 35; 35; 35; 314; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 35; 314; 264; 35; 35; 35; 35; 314; 314; 314; 314; 1; 35; 35; 35; 314; 1; 35; 35; 314; 314; 1; 1; 35; 314; 314; 1; 1; 314; 314; 1; 1; 1; 314; 1; 1; 1; 1; 1; 1; 1; 314; 1; 1; 1; 1; 314; 1; 1; 1; 314; 314; 314; 1; 264; 264; 314; 1; 1; 1; 1; 1; 264; 314; 1; 1; 1; 264; 264; 264; 314; 264; 264; 35; 1; 264; 1; 1; 1; 264; 264; 1; 1; 264; 264; 264; 264; 1; 264; 264; 314; 314; 314; 314; 314; 314; 314; 1; 1; 264; 264; 264; 264; 264; 264; 314; 314; 314; 1; 1; 264; 264; 314; 314; 314; 314; 1; 1; 264; 314; 314; 314; 314; 314; 1; 1; 314; 314; 1; 314; 314; 1; 1; 1; 314; 264; 264; 1; 1; 1; 314; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 494; 1; 494; 494; 494; 494; 1; 494; 494; 494; 494; 494; 494; 494; 494; 494; 494]';
y=x.replace(';',',')
print(y)