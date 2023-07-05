#include<bits/stdc++.h>

using namespace std;


bool isProposserFree(int proposerPartner[], int n) { // ITS WORKING FINE
    for(int i = 0; i < n; i++) {
        if(proposerPartner[i] == -1) {
            return true;
        }
    }
    return false;
}

int getFreeProposer(int proposerPartner[], int n) { // ITS WORKING FINE
    for(int i = 0; i < n; i++) {
        if(proposerPartner[i] == -1) {
            return i;
        }
    }
    return -1;
}


int findIndex(int arr[], int item, int n) { // ITS WORKING FINE
    for(int i = 0; i < n; i++) {
        if(arr[i] == item) {
            return i;
        }
    }
    return -1;
}


// ARE THOSE ARRAYS UPDATES WELL?
void proposedAcceptRequest(int proposerPartner[], int proposedPartner[], int nextPrefer[], int proposer, int proposed) {
    proposerPartner[proposer] = proposed;
    proposedPartner[proposed] = proposer;
    nextPrefer[proposer]++;
}



int main() {

    // variables
    int n;
    cout << "Enter number of proposer and proposed: \n";
    cin >> n;
    int preferProposer[n][n];
    int preferProposed[n][n];
    int nextPrefer[n];
    int proposerPartner[n];
    int proposedPartner[n];
    int k;
    bool flag = false;

    cout << "Enter preferences for proposer: \n";
    // initial data 
    for(int i = 0; i < n; i++) {
        cout << "Enter " << i + 1 << "th proposer's \n";
        for(int j = 0; j < n; j++) {
            cin >> k; 
            preferProposer[i][j] = k -1;
        }
    }

    cout << "Enter preferences for proposed: \n";
    for(int i = 0; i < n; i++) {
        cout << "Enter " << i + 1 << "th proposed's \n";
        for(int j = 0; j < n; j++) {
            cin >> k; 
            preferProposed[i][j] = k -1;
        }
    }


    for (int i = 0; i < n; i++) {
        nextPrefer[i] = 0;
        proposerPartner[i] = -1;
        proposedPartner[i] = -1;
    }


    // main logic
    while(isProposserFree(proposerPartner, n)) {
        int proposer = getFreeProposer(proposerPartner, n);
        int proposed = preferProposer[proposer][nextPrefer[proposer]];
        if (proposedPartner[proposed] == -1)
            flag = true;
        else if (findIndex(preferProposed[proposed], proposer, n) < findIndex(preferProposed[proposed], proposedPartner[proposed], n)) {
            proposerPartner[proposedPartner[proposed]] = -1;
            flag = true;
        }
        else
            flag = false;
        if(flag)
            proposedAcceptRequest(proposerPartner, proposedPartner, nextPrefer, proposer, proposed);
        else {
            nextPrefer[proposer]++;
        }
    }

    // output
    cout << "<Proposer ID> Partnered with <Proposed ID>: \n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << " Get Married With " << proposerPartner[i] + 1 << endl;
    }
    cout << "All Is Stable! =)" << endl;


}

