# house.py

class HousePark:
    lastname = "박"

    def __init__(self, name):
        self.fullname = self.lastname + name

    def travel(self, where):
        print("%s, travel to %s" % (self.fullname, where))

    def love(self, other):
        print("%s, fall in love with %s" % (self.fullname, other.fullname))

    def fight(self, other):
        print("%s fight to %s" %(self.fullname, other.fullname))
    def __add__(self, other):
        print("%s married to %s" % (self.fullname, other.fullname))
    def __sub__(self, other):
        print("%s divorce with %s" %(self.fullname, other.fullname))


class HouseKim(HousePark):
    lastname = "김"

    def travel(self, where, day):
        print("%s go to %s, for %d days" % (self.fullname, where, day))


pey = HousePark("응용")
juliet = HouseKim("줄리엣")
pey.travel('부산')
juliet.travel("부산", 3)
pey.love(juliet)
pey + juliet
pey.fight(juliet)
pey - juliet
