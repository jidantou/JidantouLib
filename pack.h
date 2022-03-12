#ifndef PACK_H
#define PACK_H

namespace jidantou
{
    class pack
    {
    private:
    public:
        pack();
        virtual bool packfile() = 0;
        virtual bool unpackfiles() = 0;
        virtual ~pack() = 0;
    };

    class _packing : public pack
    {
    private:
        /* data */
    public:
        _packing(/* args */);
        ~_packing();
    };

    class _unpacking : public pack
    {
    private:
        /* data */
    public:
        _unpacking(/* args */);
        ~_unpacking();
    };

    extern void setmode();
}
#endif