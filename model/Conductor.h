#ifndef CONDUCTOR_H
#define CONDUCTOR_H

#include "ModelElement.h"
#include "Node.h"

namespace q2d {
namespace model {

// TODO documentation
// TODO visitor-pattern
// TODO direction?
// TODO implementation
class Conductor : public ModelElement {
private:
    Node* start;
    Node* end;
public:
    Conductor(Node* start, Node* end, Model* model);
};

} // namespace model
} // namespace q2d

#endif // CONDUCTOR_H
