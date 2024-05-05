#ifndef DA2324_PRJ2_G29_NODE_H
#define DA2324_PRJ2_G29_NODE_H


class Node {
public:
    Node(int id, double longitude, double latitude) : id(id), longitude(longitude), latitude(latitude) {}

    int getId() const {
        return id;
    }

    double getLongitude() const {
        return longitude;
    }

    double getLatitude() const {
        return latitude;
    }
private:
    int id;
    double longitude;
    double latitude;
};


#endif //DA2324_PRJ2_G29_NODE_H