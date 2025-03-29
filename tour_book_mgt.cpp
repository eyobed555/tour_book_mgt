#include <iostream>
#include <string>
using namespace std;

// Structure for Tour
struct Tour {
    int id;
    string destination;
    string date;
    int availableSeats;
};

// Structure for Booking
struct Booking {
    int bookingId;
    string customerName;
    int tourId;
    Booking* next;
};

// Linked List for Bookings
class BookingList {
    private:
        Booking* head;
    
    public:
        BookingList() : head(nullptr) {}
        //To add booking 
        void addBooking(int bookingId, string customerName, int tourId) {
            Booking* newBooking = new Booking{bookingId, customerName, tourId, nullptr};
            if (!head) {
                head = newBooking;
            } else {
                Booking* temp = head;
                while (temp->next) {
                    temp = temp->next;
                }
                temp->next = newBooking;
            }
            cout << "Booking added successfully!\n";
        }

        //To cancel booking 
        void cancelBooking(int bookingId) {
            if (!head) {
                cout << "No bookings found!\n";
                return;
            }
            if (head->bookingId == bookingId) {
                Booking* temp = head;
                head = head->next;
                delete temp;
                cout << "Booking canceled successfully!\n";
                return;
            }
            Booking* temp = head;
            while (temp->next && temp->next->bookingId != bookingId) {
                temp = temp->next;
            }
            if (temp->next) {
                Booking* toDelete = temp->next;
                temp->next = temp->next->next;
                delete toDelete;
                cout << "Booking canceled successfully!\n";
            } else {
                cout << "Booking not found!\n";
            }
        }
        //To display booking
        void displayBookings() {
            if (!head) {
                cout << "No bookings found!\n";
                return;
            }
            Booking* temp = head;
            while (temp) {
                cout << "Booking ID: " << temp->bookingId << ", Customer: " << temp->customerName << ", Tour ID: " << temp->tourId << "\n";
                temp = temp->next;
            }
        }
    };

// Array for Tours
Tour tours[100];
int tourCount = 0;

// Add a new tour
void addTour(int id, string destination, string date, int availableSeats) {
    tours[tourCount++] = {id, destination, date, availableSeats};
    cout << "Tour added successfully!\n";
}

// Search for a tour by ID
Tour* searchTour(int id) {
    for (int i = 0; i < tourCount; i++) {
        if (tours[i].id == id) {
            return &tours[i];
        }
    }
    return nullptr;
}

// Update a tour
void updateTour(int id, string destination, string date, int availableSeats) {
    Tour* tour = searchTour(id);
    if (tour) {
        tour->destination = destination;
        tour->date = date;
        tour->availableSeats = availableSeats;
        cout << "Tour updated successfully!\n";
    } else {
        cout << "Tour not found!\n";
    }
}

//To delete tour
void deleteTour(int id) {
    for (int i = 0; i < tourCount; i++) {
        if (tours[i].id == id) {
            for (int j = i; j < tourCount - 1; j++) {
                tours[j] = tours[j + 1];
            }
            tourCount--;
            cout << "Tour deleted successfully!\n";
            return;
        }
    }
    cout << "Tour not found!\n";
}

// Display all tours
void displayTours() {
    if (tourCount == 0) {
        cout << "No tours available!\n";
        return;
    }
    for (int i = 0; i < tourCount; i++) {
        cout << "Tour ID: " << tours[i].id << ", Destination: " << tours[i].destination
             << ", Date: " << tours[i].date << ", Available Seats: " << tours[i].availableSeats << "\n";
    }
}

int main(){
    BookingList bookings;
    int choice;

    do {
        cout << "\nTour Booking & Travel Package Management\n";
        cout << "1. Add Tour\n";
        cout << "2. Search Tour\n";
        cout << "3. Update Tour\n";
        cout << "4. Delete Tour\n";
        cout << "5. Display Tours\n";
        cout << "6. Book Tour\n";
        cout << "7. Cancel Booking\n";
        cout << "8. Display Bookings\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, seats;
                string destination, date;
                cout << "Enter Tour ID: ";
                cin >> id;
                cout << "Enter Destination: ";
                cin >> destination;
                cout << "Enter Date: ";
                cin >> date;
                cout << "Enter Available Seats: ";
                cin >> seats;
                addTour(id, destination, date, seats);
                break;
            }
            case 2: {
                int id;
                cout << "Enter Tour ID to search: ";
                cin >> id;
                Tour* tour = searchTour(id);
                if (tour) {
                    cout << "Tour Found: " << tour->destination << " on " << tour->date << "\n";
                } else {
                    cout << "Tour not found!\n";
                }
                break;
            }
            case 3: {
                int id, seats;
                string destination, date;
                cout << "Enter Tour ID to update: ";
                cin >> id;
                cout << "Enter New Destination: ";
                cin >> destination;
                cout << "Enter New Date: ";
                cin >> date;
                cout << "Enter New Available Seats: ";
                cin >> seats;
                updateTour(id, destination, date, seats);
                break;
            }
            case 4: {
                int id;
                cout << "Enter Tour ID to delete: ";
                cin >> id;
                deleteTour(id);
                break;
            }
            case 5: {
                displayTours();
                break;
            }
            case 6: {
                int bookingId, tourId;
                string customerName;
                cout << "Enter Booking ID: ";
                cin >> bookingId;
                cout << "Enter Customer Name: ";
                cin >> customerName;
                cout << "Enter Tour ID: ";
                cin >> tourId;
                bookings.addBooking(bookingId, customerName, tourId);
                break;
            }
            case 7: {
                int bookingId;
                cout << "Enter Booking ID to cancel: ";
                cin >> bookingId;
                bookings.cancelBooking(bookingId);
                break;
            }
            case 8: {
                bookings.displayBookings();
                break;
            }
            case 9: {
                cout << "Exiting...\n";
                break;
            }
            default: {
                cout << "Invalid choice! Try again.\n";
            }

        }
    } while (choice != 9);
    
    return 0;
}