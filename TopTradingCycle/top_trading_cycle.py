class Vertex:
    def __init__(self, name):
        self.id = name
        self.outGoing = []
        self.inComing = []
        self.visited = False

    def __repr__(self):
        return self.id
    
    def __str__(self) -> str:
        return self.id
    
    def degree(self):
        return len(self.outGoing) + len(self.inComing)

    def add_out_edge(self, vertex):
        self.outGoing.append(vertex)

    def remove_out_edge(self, vertex):
        self.outGoing.remove(vertex)
    
    def add_in_edge(self, vertex):
        self.inComing.append(vertex)

    def remove_in_edge(self, vertex):
        self.inComing.remove(vertex)
    

class Graph:
    def __init__(self, vertices):
        self.vertices = list(v for v in vertices)
        self.edges = []

    def add_vertex(self, vertex):
        self.vertices.append(vertex)

    def add_edge(self, income_vertex, outcome_vertex):
        self.edges.append((income_vertex.id, outcome_vertex.id))
        income_vertex.add_out_edge(outcome_vertex)
        outcome_vertex.add_in_edge(income_vertex)

    def remove_edge(self, income_vertex, outcome_vertex):
        self.edges.remove((income_vertex.id, outcome_vertex.id))
        income_vertex.remove_out_edge(outcome_vertex)
        outcome_vertex.remove_in_edge(income_vertex)
    
    def remove_vertex(self, vertex):
        self.vertices.remove(vertex)
        copyIncoming = vertex.inComing.copy()
        for v in copyIncoming:
            self.remove_edge(v, vertex)
        copyOutgoing = vertex.outGoing.copy()
        for v in copyOutgoing:
            self.remove_edge(vertex, v)
    
    def get_edge(self, income_vertex, outcome_vertex):
        return (income_vertex.id, outcome_vertex.id) in self.edges

    def find_cycle(self):
        visited = set()
        cycle = set()
        v = self.vertices[0]
        while v not in visited:
            visited.add(v)
            v = v.outGoing[0]
        starting_vertex = (v.outGoing[0])
        while starting_vertex not in cycle:
            cycle.add(starting_vertex)
            starting_vertex = (starting_vertex.outGoing[0])
        return sorted(cycle, key=lambda obj: obj.id)


# top trading cycle input / initialization
n = int(input())
list_of_users = [list(map(int, input().split())) for _ in range(n)]
list_of_vertices = [Vertex(i) for i in range(n)]
data_object = {vertex.id: {"pref": pref, "nextPointer": 0} for vertex, pref in zip(list_of_vertices, list_of_users)}
graph = Graph(list_of_vertices)


# connect vertices to their first preference
for i in range(n):
    vertex = list_of_vertices[i]
    graph.add_edge(vertex, list_of_vertices[((data_object[vertex.id]["pref"])[data_object[vertex.id]["nextPointer"]]) - 1])
    data_object[vertex.id]["nextPointer"] += 1

def find_next_preference(vertex):
    while (searchInConnectedArray(connected_components, (data_object[vertex.id]["pref"])[data_object[vertex.id]["nextPointer"]] )):
        data_object[vertex.id]["nextPointer"] += 1
    return ((data_object[vertex.id]["pref"])[data_object[vertex.id]["nextPointer"]])


def searchInConnectedArray(array, key):
    for i in range(len(array)):
        a, b = array[i].split(" => ")
        if (a == str(key)):
            return 1
    return 0


connected_components = []
while len(connected_components) != len(list_of_vertices):
    cycle = graph.find_cycle()
    for vertex in cycle:
        connected_components.append(f"{vertex.id + 1} => {vertex.outGoing[0].id + 1}")
    for vertex in cycle:
        for anyIncomingVertex in vertex.inComing:
            if anyIncomingVertex not in cycle:
                graph.add_edge(anyIncomingVertex, list_of_vertices[find_next_preference(anyIncomingVertex) - 1])
                data_object[anyIncomingVertex.id]["nextPointer"] += 1
        graph.remove_vertex(vertex)


for i in connected_components:
    print(i)

