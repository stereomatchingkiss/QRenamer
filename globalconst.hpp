#ifndef GLOBALCONST_HPP
#define GLOBALCONST_HPP

enum class fileNameHeader{
    Path, OldName, NewName,
    OldSuffix, NewSuffix,
    LastElem
};

enum class filterType{
    Exclude, Include
};

enum class RenameType{
    Base, Suffix, BaseAndSuffix
};

#endif // GLOBALCONST_HPP

