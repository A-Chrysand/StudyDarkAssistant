class girl:
	name = ""
	age = 0

class People:
	def __init__(self):
		self.data = [girl()]

	def AddEmptyOne(self):
		self.data.append(girl())

	def Addone(self, name, age):
		self.AddEmptyOne()
		self.data[-1].name = name
		self.data[-1].age = age

	def DeletOne(self, i):
		self.data.remove(i)

	def Print(self, i=None):
		if (i == None):
			i = -1
		print("name:"+self.data[i].name+" age:"+str(self.data[i].age))

people = People()  # 创建一个lp