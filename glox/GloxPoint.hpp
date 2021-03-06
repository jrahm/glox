#ifndef GLOXPOINT_HPP_
#define GLOXPOINT_HPP_

/*
 * Author: jrahm
 * created: 2013/10/22
 * GloxPoint.hpp: <description>
 */

#include "glox/GloxCommon.hpp"
#include "glox/GloxPlottable.hpp"
#include "glox/GloxVectorizable.hpp"
#include "glox/GloxVector4.hpp"

#include <iostream>
#include <string>
#include <sstream>

#include <cmath>

namespace glox {

/* Type that the GloxPoint holds,
 * defaults to an integer */
template <class NumT=float>

/* A point in 3D space. This class
 * implements Plottable which provides
 * the `plot` function which calles
 * glVertex on the components */
class GloxPoint : public GloxPlottable,GloxVectorizable<NumT> {
public:
	inline static GloxPoint<> fromSpherical( NumT r, NumT th, NumT ph ) {
   // double Ex = -2*dim*Sin(th)*Cos(ph);
   // double Ey = +2*dim        *Sin(ph);
   // double Ez = +2*dim*Cos(th)*Cos(ph);
		return GloxPoint<>( -r * GloxSin( th ) * GloxCos( ph ),
		                     r * GloxSin( ph ),
							 r * GloxCos( th ) * GloxCos( ph ) ) ;
	}
	
	inline static GloxPoint<> fromSpherical( const GloxVector4<NumT>& vec ) {
		return fromSpherical( vec.getX(), vec.getY(), vec.getZ() );
	}

	/* Creates a new GloxPoint from the components
	 * specified */
	inline GloxPoint( const NumT& x=0, const NumT& y=0, const NumT& z=0 ):
		x(x), y(y), z(z) {}

	/* Copies the glox point other */
	inline GloxPoint( const GloxPoint<NumT>& other ) :
		x(other.x), y(other.y), z(other.z) {}

	/* Returns the X componet of this
	 * point */
	inline const NumT& getX() const {
		return x;
	}

	/* Returns the Y component of this
	 * point */
	inline const NumT& getY() const {
		return y;
	}

	/* Returns the Z component of this
	 * point */
	inline const NumT& getZ() const {
		return z;
	}

	/* Sets the X component of this
	 * point */
	inline void setX( const NumT& x ) {
		this->x = x;
	}

	/* Sets the Y component of this point */
	inline void setY( const NumT& y ) {
		this->y = y;
	}

	/* Sets the Z component of this
	 * point */
	inline void setZ( const NumT& z ) {
		this->z = z;
	}

    inline float getMagnitude() const {
        return sqrt( x * x + y * y + z * z ) ;
    }

	/* Copy the point `point` into this
	 * point */
	inline const GloxPoint<NumT>& operator=( const GloxPoint<NumT>& point ) {
		this->x = point.x;
		this->y = point.y;
		this->z = point.z;

		return * this;
	}

	/* Add the components of `point` to this */
	inline GloxPoint<NumT>& operator+=( const GloxPoint<NumT>& point ) {
		this->x += point.x;
		this->y += point.y;
		this->z += point.z;

		return * this;
	}

	/* Add the components of `point` to this */
	inline GloxPoint<NumT>& operator-=( const GloxPoint<NumT>& point ) {
		this->x -= point.x;
		this->y -= point.y;
		this->z -= point.z;

		return * this;
	}

	/* Returns a new GloxPoint that is the sum
	 * of this and `point` */
	inline GloxPoint<NumT> operator+( const GloxPoint<NumT>& point ) const {
		GloxPoint<NumT> ret = *this;
		ret += point;
		return ret;
	}

	/* Returns a new GloxPoint that is the sum
	 * of this and `point` */
	inline GloxPoint<NumT> operator-( const GloxPoint<NumT>& point ) const {
		GloxPoint<NumT> ret = *this;
		ret -= point;
		return ret;
	}

	inline GloxPoint<NumT>& operator*=( NumT scalar ) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return * this;
	}

	inline GloxPoint<NumT> operator*(NumT scalar) const {
		GloxPoint<NumT> ret = * this;
		ret *= scalar;
		return ret;
	}

    inline NumT dot( const GloxPoint<NumT>& other ) {
        GloxPoint<> tmp1 = *this;
        GloxPoint<> tmp2 = other;

        // std::cout << "Orig: " << this->toString() << ", " << other.toString() << std::endl;
        tmp1.normalize();
        tmp2.normalize();

        // std::cout << "Norm: " << this->toString() << ", " << other.toString() << std::endl;;
        return tmp1.x * tmp2.x +
               tmp1.y * tmp2.y +
               tmp1.z * tmp2.z ;
    }

    inline GloxPoint<NumT> cross( const GloxPoint<NumT>& other ) {
        return GloxPoint( 
              y * other.z - z * other.y
            , z * other.x - x * other.z
            , x * other.y - y * other.x
        );
    }

    inline void normalize() {
        float mag = getMagnitude();

        x = x / mag;
        y = y / mag;
        z = z / mag;
    }

    inline std::string toString() const {
        std::stringstream stream;
        stream << "( " << x << ", " << y << ", " << z << " )";
        return stream.str();
    }

    virtual inline void scale( NumT amt ) {
        x *= amt; y *= amt; z *= amt;
    }

    int toVector( NumT* arr, size_t len ) const {
        if( len < 3 ) return -1;
        arr[0] = x;
        arr[1] = y;
        arr[2] = z;
        return 3;
    }

	/* Plot this point. This function depends on the
	 * number provided */
	inline void plot( ) const;
private:
	NumT x;
	NumT y;
	NumT z;
};

typedef GloxPoint<> GloxPointf;

/* Implementations of the plot functions for
 * different template arguments */
template <>
inline void GloxPoint<int>::plot() const {
    glVertex3i( this->getX(), this->getY(), this->getZ() );
}
template <>
inline void GloxPoint<float>::plot() const {
    glVertex3f( this->getX(), this->getY(), this->getZ() );
}
template <>
inline void GloxPoint<short>::plot() const {
    glVertex3s( this->getX(), this->getY(), this->getZ() );
}
template <class T>
inline void GloxPoint<T>::plot() const {
    glVertex3d( this->getX(), this->getY(), this->getZ() );
}

}

#endif /* GLOXPOINT_HPP_ */
