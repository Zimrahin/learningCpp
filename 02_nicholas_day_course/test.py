class Base:
    def __init__(self, id):
        self.id = id
        print(f"Base Non-Default Constructor, id = {id}")


class Derived(Base):
    def __init__(self, id):
        super().__init__(id)  # Calls the constructor of the base class
        print(f"Derived Non-Default Constructor, id = {id}")


obj = Derived(3)
