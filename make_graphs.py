import pandas as pd
import matplotlib.pyplot as plt
from math import asin, pi

df = pd.read_csv('data.csv')

exact_value = 0.25 * pi + 1.25 * asin(0.8) - 1.0

# График 1 типа: приближенная площадь от N
plt.figure(figsize=(10, 5))
plt.plot(df['N'], df['Wide_Area'], label='Широкая область')
plt.plot(df['N'], df['Narrow_Area'], label='Узкая область')
plt.axhline(y=exact_value, color='red', linestyle='--', label=f'Точное значение ({exact_value:.4f})')
plt.xlabel('Количество точек N')
plt.ylabel('Приближенная площадь')
plt.title('Зависимость площади от количества точек')
plt.legend()
plt.grid(True)
plt.show()

# График 2 типа: относительная ошибка от N
plt.figure(figsize=(10, 5))
plt.semilogy(df['N'], df['Wide_Error'], label='Широкая область')
plt.semilogy(df['N'], df['Narrow_Error'], label='Узкая область')
plt.xlabel('Количество точек N')
plt.ylabel('Относительная ошибка (%)')
plt.title('Зависимость ошибки от количества точек')
plt.legend()
plt.grid(True)
plt.show()