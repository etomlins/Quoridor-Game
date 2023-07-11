#include "board.hxx"
#include "model.hxx"

std::ostream& operator<<
(std::ostream& os, Player playerType) {
    switch (playerType) {
    case Player::rachel:
        return os << "WHERE'S RACHEL. WHERE IS SHE";
    case Player::bruce:
        return os << "I AM BATMAN";
    default:
        return os << "_";
    }
}
