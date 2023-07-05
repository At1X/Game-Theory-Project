people_number = int(input("Number of people: "))
propossers = [[]]
propossed = [[]]
print("Enter the preferences of the Proposers: ")
for i in range(1, people_number + 1):
    print("Person " + str(i) + " preferences: ", end="")
    propossers.append(list(map(int, input().split())))


print("\nEnter the preferences of the Proposed: ")
for i in range(1, people_number + 1):
    print("Person " + str(i) + " preferences: ", end="")
    propossed.append(list(map(int, input().split())))
print(propossers)


# create next_prop
next_prop = [0 for i in range(people_number + 1)]


# create data_dict 
data_dict = {
    "propossers": {},
    "propossed": {}
}
for i in range(1, people_number + 1):
    data_dict["propossers"][i] = 0
    data_dict["propossed"][i] = 0



def isProposserBetter(given,  taken) -> bool:
    if (data_dict["propossed"][taken] == 0):
        return True
    else:
        if (propossed[taken].index(given) < propossed[taken].index(data_dict["propossed"][taken])):
            data_dict["propossers"][data_dict["propossed"][taken]] = 0
            return True

def isProposserFree(given) -> bool:
    return data_dict["propossers"][given] == 0


def propossedAccepts(given, taken):
    data_dict["propossers"][given] = int(taken)
    data_dict["propossed"][taken] = int(given)
    next_prop[int(given)] += 1


def propose(given, taken):
    if isProposserBetter(given, taken):
        propossedAccepts(given, taken)
    else:
        next_prop[int(given)] += 1
        propose(given, propossers[int(given)][next_prop[int(given)]])


while(0 in data_dict["propossers"].values()):
    for i in range(1, people_number + 1):   
        if isProposserFree(i):
            propose(i, propossers[i][next_prop[i]])
