import openpyxl

wb = openpyxl.load_workbook('./ad.xlsx')
Class1 = wb['1반']


print(Class1.value)
wb.close()
