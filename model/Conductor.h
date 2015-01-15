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
    static int DEFAULT_NAME_INDEX;

    Node* start;
    Node* end;
public:
    Conductor(Node *start, Node* end);
};

} // namespace model
} // namespace q2d

#endif // CONDUCTOR_H
