#include <iostream>
#include <cstring>

using namespace std;

class Computer {
private:
	static int objectId; 
	char* model;
	char* vendor;
	char* videocard;
	float cpu_hz;
	int ram;
	int disk_size;
	bool SSD;

public:
	Computer() {
		model = nullptr;   
		vendor = nullptr;     
		videocard = nullptr; 
		cpu_hz = 0.0f;       
		ram = 0;             
		disk_size = 0;    
		SSD = false;        
	}

	Computer(const char* model, const char* vendor, const char* videocard, float cpu_hz, int ram, int disk_size, bool SSD) {
		this->cpu_hz = cpu_hz;
		
		this->ram = ram;
		
		this->disk_size = disk_size;
		
		this->SSD = SSD;

		this->model = new char[strlen(model) + 1];
		strcpy_s(this->model, strlen(model) + 1, model); 

		this->vendor = new char[strlen(vendor) + 1];
		strcpy_s(this->vendor, strlen(vendor) + 1, vendor);

		this->videocard = new char[strlen(videocard) + 1];
		strcpy_s(this->videocard, strlen(videocard) + 1, videocard);
	}

	~Computer() {
		delete[] model;
		delete[] vendor;
		delete[] videocard;
	}

	char* GetModel() const { return model; }
	char* GetVendor() const { return vendor; }
	char* GetVideoCard() const { return videocard; }
	float GetCpu() const { return cpu_hz; }
	int GetRam() const { return ram; }
	int GetDiskSize() const { return disk_size; }
	bool GetSSD() const { return SSD; }

	friend ostream& operator<<(ostream& os, const Computer& comp) {
		os << "Model: " << comp.model << endl
			<< "Vendor: " << comp.vendor << endl
			<< "Video Card: " << comp.videocard << endl
			<< "CPU: " << comp.cpu_hz << " GHz" << endl
			<< "RAM: " << comp.ram << " GB" << endl
			<< "Disk Size: " << comp.disk_size << " GB" << endl
			<< "SSD: " << (comp.SSD ? "Yes" : "No") << endl;
		return os;
	}
};

int Computer::objectId = 0;

class Computer_store {
	char* store_name;
	char* store_address;
	Computer** computers;
	int computer_count;

public:
	Computer_store(const char* store_name, const char* store_address) {
		this->store_name = new char[strlen(store_name) + 1];
		strcpy_s(this->store_name, strlen(store_name) + 1, store_name);

		this->store_address = new char[strlen(store_address) + 1];
		strcpy_s(this->store_address, strlen(store_address) + 1, store_address);

		computers = nullptr; 
		computer_count = 0;  
	}

	~Computer_store() {
		delete[] store_name;
		delete[] store_address;
		delete[] computers;
	}

	
	void addComputer(Computer* computer) {
		Computer** new_computers = new Computer * [computer_count + 1];
		for (int i = 0; i < computer_count; ++i) {
			new_computers[i] = computers[i];
		}
		new_computers[computer_count] = computer;
		delete[] computers; 
		computers = new_computers; 
		computer_count++; 
	}
	
	void removeComputer(int index) {
		if (index < 0 || index >= computer_count) {
			cout << "Invalid index!" << endl;
			return;
		}

		delete computers[index];

		Computer** new_computers = new Computer * [computer_count - 1];
		for (int i = 0, j = 0; i < computer_count; ++i) {
			if (i != index) {
				new_computers[j++] = computers[i];
			}
		}

		delete[] computers;
		computers = new_computers;
		computer_count--;
	}

	void displayComputers() const {
		for (int i = 0; i < computer_count; ++i) {
			cout << *computers[i] << endl;
		}
	}
};

int main() {
	Computer_store store("Tech Store", "123 Tech Ave");

	Computer* comp1 = new Computer("MSI", "Vendor A", "RTX 3080", 2.3f, 16, 512, true);
	Computer* comp2 = new Computer("Dell", "Vendor B", "GTX 1660", 2.0f, 8, 256, false);

	store.addComputer(comp1);
	store.addComputer(comp2);
	store.removeComputer(1);
	store.displayComputers();

	return 0;
}
