#include "position.h"
#include "exceptions.h"

Position::Position(char file, int rank):
        file(file),
        rank(rank) {
    if (!std::count(std::begin(FILES), std::end(FILES), file) || rank < 1 || rank > N) {
        throw IncorrectPositionException();
    }
}

bool Position::operator<(const Position& position) const {
    return file < position.file || (file == position.file && rank < position.rank);
}
