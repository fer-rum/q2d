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
    Node* m_start;
    Node* m_end;
public:
    Conductor(Node* start, Node* end, Model* model, DocumentEntry* relatedEntry = nullptr);
};

} // namespace model
} // namespace q2d

#endif // CONDUCTOR_H
