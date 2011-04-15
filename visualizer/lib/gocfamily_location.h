#ifndef GOCFAMILY_LOCATION_H
#define GOCFAMILY_LOCATION_H

class GOCFamily_Location
{
public:
    GOCFamily_Location()
    {
	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_dir = 0;
    }

    const GOC_IDType familyID() const
    {
    return GOC_IDType( "LocationFamily" );
    };

    int x();
    int y();
    int z();
    int dir();

    private:
    int m_x, m_y, m_z, m_dir;

};



#endif // GOCFAMILY_LOCATION_H
