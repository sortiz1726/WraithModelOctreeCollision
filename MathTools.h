#ifndef _MathTools
#define _MathTools

#include <algorithm>
#include <cassert>

class Matrix;
class Vect;
class CollisionVolume;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class CollisionVolumeOctree;
class Triangle;

/**********************************************************************************************//**
// namespace: MathTools
//
// summary:	A places where are tools to be used by engine and even the user.
 **************************************************************************************************/
namespace MathTools
{
	// Intersections

	/**********************************************************************************************//**
	* <summary> Test intersection between two collision volumes.</summary>
	*
	* <remarks> </remarks>
	*
	* <param name="collisionVolume_1"> The first collision volume.</param>
	* <param name="collisionVolume_2"> The second collision volume.</param>
	*
	* <returns> True if it succeeds, false if it fails.</returns>
	**************************************************************************************************/
	bool Intersect(const CollisionVolume& collisionVolume_1, const CollisionVolume& collisionVolume_2);

	/**********************************************************************************************//**
	 * <summary> Test intersection between two BSpheres.</summary>
	 *	\ingroup MATHTOOLS
	 * <remarks> </remarks>
	 *
	 * <param name="BSphere_1"> The first sphere.</param>
	 * <param name="BSphere_2"> The second sphere.</param>
	 *
	 * <returns> True if it succeeds, false if it fails.</returns>
	 **************************************************************************************************/
	bool Intersect(const CollisionVolumeBSphere& BSphere_1, const CollisionVolumeBSphere& BSphere_2);

	/**********************************************************************************************//**
	* <summary> Test intersection between BSphere and AABB.</summary>
	*	\ingroup MATHTOOLS
	* <remarks> </remarks>
	*
	* <param name="BSphere"> A BSphere.</param>
	* <param name="AABB"> An AABB.</param>
	*
	* <returns> True if it succeeds, false if it fails.</returns>
	**************************************************************************************************/
	bool Intersect(const CollisionVolumeBSphere& BSphere, const CollisionVolumeAABB& AABB);

	/**********************************************************************************************//**
	* <summary> Test intersection between BSphere and OBB.</summary>
	*	\ingroup MATHTOOLS
	* <remarks> </remarks>
	*
	* <param name="BSphere"> A BSphere.</param>
	* <param name="OBB"> An OBB.</param>
	*
	* <returns> True if it succeeds, false if it fails.</returns>
	**************************************************************************************************/
	bool Intersect(const CollisionVolumeBSphere& BSphere, const CollisionVolumeOBB& OBB);

	/**********************************************************************************************//**
	* <summary> Test intersection between BSphere and Octree.</summary>
	*	\ingroup MATHTOOLS
	* <remarks> </remarks>
	*
	* <param name="BSphere"> A BSphere.</param>
	* <param name="Octree"> An Octree.</param>
	*
	* <returns> True if it succeeds, false if it fails.</returns>
	**************************************************************************************************/
	bool Intersect(const CollisionVolumeBSphere& BSphere, const CollisionVolumeOctree& Octree);

	/**********************************************************************************************//**
	* <summary> Test intersection between two AABBs.</summary>
	*	\ingroup MATHTOOLS
	* <remarks> </remarks>
	*
	* <param name="AABB_1"> An AABB.</param>
	* <param name="AABB_2"> An AABB.</param>
	*
	* <returns> True if it succeeds, false if it fails.</returns>
	**************************************************************************************************/
	bool Intersect(const CollisionVolumeAABB& AABB_1, const CollisionVolumeAABB& AABB_2);

	/**********************************************************************************************//**
	* <summary> Test intersection between AABB and OBB.</summary>
	*	\ingroup MATHTOOLS
	* <remarks> </remarks>
	*
	* <param name="AABB"> An AABB.</param>
	* <param name="OBB"> An OBB.</param>
	*
	* <returns> True if it succeeds, false if it fails.</returns>
	**************************************************************************************************/
	bool Intersect(const CollisionVolumeAABB& AABB, const CollisionVolumeOBB& OBB);

	/**********************************************************************************************//**
	* <summary> Test intersection between AABB and Octree.</summary>
	*	\ingroup MATHTOOLS
	* <remarks> </remarks>
	*
	* <param name="AABB"> An AABB.</param>
	* <param name="Octree"> An Octree.</param>
	*
	* <returns> True if it succeeds, false if it fails.</returns>
	**************************************************************************************************/
	bool Intersect(const CollisionVolumeAABB& AABB, const CollisionVolumeOctree& Octree);

	/**********************************************************************************************//**
	* <summary> Test intersection between two OBBs.</summary>
	*	\ingroup MATHTOOLS
	* <remarks> </remarks>
	*
	* <param name="OBB_1"> An OBB.</param>
	* <param name="OBB_2"> An OBB.</param>
	*
	* <returns> True if it succeeds, false if it fails.</returns>
	**************************************************************************************************/
	bool Intersect(const CollisionVolumeOBB& OBB_1, const CollisionVolumeOBB& OBB_2);

	/**********************************************************************************************//**
	* <summary> Test intersection between an OBB and an Octree.</summary>
	*	\ingroup MATHTOOLS
	* <remarks> </remarks>
	*
	* <param name="OBB"> An OBB.</param>
	* <param name="Octree"> An Octree.</param>
	*
	* <returns> True if it succeeds, false if it fails.</returns>
	**************************************************************************************************/
	bool Intersect(const CollisionVolumeOBB& OBB, const CollisionVolumeOctree& Octree);

	/**********************************************************************************************//**
	* <summary> Test intersection between two Octrees.</summary>
	*	\ingroup MATHTOOLS
	* <remarks> </remarks>
	*
	* <param name="Octree_1"> An Octree.</param>
	* <param name="Octree_2"> An Octree.</param>
	*
	* <returns> True if it succeeds, false if it fails.</returns>
	**************************************************************************************************/
	bool Intersect(const CollisionVolumeOctree& Octree_1, const CollisionVolumeOctree& Octree_2);

	bool Intersect(const CollisionVolume& collisionVolume, const CollisionVolumeOctree& Octree);

	/**********************************************************************************************//**
	* <summary> Test intersection between an AABB and a point.</summary>
	*	\ingroup MATHTOOLS
	* <remarks> </remarks>
	*
	* <param name="AABB"> An AABB.</param>
	* <param name="point"> A point.</param>
	*
	* <returns> True if it succeeds, false if it fails.</returns>
	**************************************************************************************************/
	bool Intersect(const CollisionVolumeAABB& AABB, const Vect& point);

	/**********************************************************************************************//**
	* <summary> Test intersection between an OBB and a point.</summary>
	*	\ingroup MATHTOOLS
	* <remarks> </remarks>
	*
	* <param name="OBB"> An OBB.</param>
	* <param name="point"> A point.</param>
	*
	* <returns> True if it succeeds, false if it fails.</returns>
	**************************************************************************************************/
	bool Intersect(const CollisionVolumeOBB& OBB, const Vect& point);

	/**********************************************************************************************//**
	* <summary> Computes and outputs all axes to test.</summary>
	*
	* <remarks> Only 15 axes are computed. </remarks>
	*
	* <param name="OBB_1"> An OBB.</param>
	* <param name="OBB_2"> An OBB.</param>
	* <param name="axes"> A array of Vect to write data to</param>
	*
	* <returns> Nothing. </returns>
	**************************************************************************************************/
	void OutputAxesToTest(const CollisionVolumeOBB& OBB_1, const CollisionVolumeOBB& OBB_2, Vect* axes);

	/**********************************************************************************************//**
	* <summary> Computes and outputs all axes to test.</summary>
	*
	* <remarks> Only 15 axes are computed. </remarks>
	*
	* <param name="AABB"> An AABB.</param>
	* <param name="OBB"> An OBB.</param>
	* <param name="axes"> A array of Vect to write data to</param>
	*
	* <returns> Nothing. </returns>
	**************************************************************************************************/
	void OutputAxesToTest(const CollisionVolumeAABB& AABB, const CollisionVolumeOBB& OBB, Vect* axes);

	/**********************************************************************************************//**
	* <summary> Determines if two Boxes overlap on specified axis.</summary>
	*
	* <remarks> The axis is pure vector, so Vect[w] must be 0. </remarks>
	*
	* <param name="OBB_1"> An OBB.</param>
	* <param name="OBB_2"> An OBB.</param>
	* <param name="axis"> An axis.</param>
	*
	* <returns>  True if it succeeds, false if it fails.</returns>
	**************************************************************************************************/
	bool DoesOverlapsOnAxis(const CollisionVolumeOBB& OBB_1, const CollisionVolumeOBB& OBB_2, const Vect& axis);

	/**********************************************************************************************//**
	* <summary> Determines if two Boxes overlap on specified axis.</summary>
	*
	* <remarks> The axis is pure vector, so Vect[w] must be 0. </remarks>
	*
	* <param name="AABB"> An AABB.</param>
	* <param name="OBB"> An OBB.</param>
	* <param name="axis"> An axis.</param>
	*
	* <returns>  True if it succeeds, false if it fails.</returns>
	**************************************************************************************************/
	bool DoesOverlapsOnAxis(const CollisionVolumeAABB& AABB, const CollisionVolumeOBB& OBB, const Vect& axis);

	/**********************************************************************************************//**
	* <summary> Computes max projections length of Box onto an axis.</summary>
	*
	* <remarks> The axis is pure vector, so Vect[w] must be 0. </remarks>
	*
	* <param name="OBB"> An OBB.</param>
	* <param name="axis"> An axis.</param>
	*
	* <returns> return Max Projection length.</returns>
	**************************************************************************************************/
	float getMaxBoxProjectionLength(const CollisionVolumeOBB& OBB, const Vect& axis);

	/**********************************************************************************************//**
	* <summary> Computes max projections length of Box onto an axis.</summary>
	*
	* <remarks> The axis is pure vector, so Vect[w] must be 0. </remarks>
	*
	* <param name="AABB"> An AABB.</param>
	* <param name="axis"> An axis.</param>
	*
	* <returns> return Max Projection length.</returns>
	**************************************************************************************************/
	float getMaxBoxProjectionLength(const CollisionVolumeAABB& AABB, const Vect& axis);

	/**********************************************************************************************//**
	* <summary> Test intersection between an OBB and a Triangle.</summary>
	*	\ingroup MATHTOOLS
	* <remarks> </remarks>
	*
	* <param name="OBB"> An OBB.</param>
	* <param name="triangle"> A triangle.</param>
	*
	* <returns> True if it succeeds, false if it fails.</returns>
	**************************************************************************************************/
	bool Intersect(const CollisionVolumeOBB& OBB, const Triangle& triangle);

	Triangle AdjustTriangle(const CollisionVolumeOBB& OBB, const Triangle& triangle);

	/**********************************************************************************************//**
	* <summary> Computes and outputs all axes to test.</summary>
	*
	* <remarks> Only 13 axes are computed. </remarks>
	*
	* <param name="OBB"> An OBB.</param>
	* <param name="triangle"> An triangle.</param>
	* <param name="axes"> A array of Vect to write data to</param>
	*
	* <returns> Nothing. </returns>
	**************************************************************************************************/
	void OutputAxesToTest(const CollisionVolumeOBB& OBB, const Triangle& triangle, Vect* axes);

	/**********************************************************************************************//**
	* <summary> Determines if Box and triangle overlap on specified axis.</summary>
	*
	* <remarks> The axis is pure vector, so Vect[w] must be 0. </remarks>
	*
	* <param name="OBB"> An OBB.</param>
	* <param name="triangle"> An triangle.</param>
	* <param name="axis"> An axis.</param>
	*
	* <returns>  True if it succeeds, false if it fails.</returns>
	**************************************************************************************************/
	bool DoesOverlapsOnAxis(const CollisionVolumeOBB& OBB, const Triangle& triangle, const Vect& axis);

	// World Matrix Decomposition

	/**********************************************************************************************//**
	 * <summary> Extracts scale matrix.</summary>
	 *	\ingroup MATHTOOLS
	 * <remarks> assumes matrix is a world matrix composed of translation, rotation and scale. </remarks>
	 *
	 * <param name="worldMatrix"> The world matrix.</param>
	 *
	 * <returns> The scale matrix.</returns>
	 **************************************************************************************************/
	Matrix ExtractScaleMatrix(const Matrix& worldMatrix);

	/**********************************************************************************************//**
	 * <summary> Extracts XYZ scale of a world matrix.</summary>
	 *	\ingroup MATHTOOLS
	 * <remarks> assumes matrix is a world matrix composed of translation, rotation and scale.</remarks>
	 *
	 * <param name="worldMatrix"> The world matrix.</param>
	 *
	 * <returns> The XYZ scale in a Vector.</returns>
	 **************************************************************************************************/
	Vect ExtractScaleXYZ(const Matrix& worldMatrix);

	/**********************************************************************************************//**
	 * <summary> Extracts X-scale from world matrix.</summary>
	 *	\ingroup MATHTOOLS
	 * <remarks> assumes matrix is a world matrix composed of translation, rotation and scale.</remarks>
	 *
	 * <param name="worldMatrix"> The world matrix.</param>
	 *
	 * <returns> The X scale.</returns>
	 **************************************************************************************************/
	float ExtractScaleX(const Matrix& worldMatrix);

	/**********************************************************************************************//**
	 * <summary> Extracts Y scale from the world matrix.</summary>
	 *	\ingroup MATHTOOLS
	 * <remarks> assumes matrix is a world matrix composed of translation, rotation and scale.</remarks>
	 *
	 * <param name="worldMatrix"> The world matrix.</param>
	 *
	 * <returns> The Y scale.</returns>
	 **************************************************************************************************/
	float ExtractScaleY(const Matrix& worldMatrix);

	/**********************************************************************************************//**
	 * <summary> Extracts Z scale from world matrix.</summary>
	 *	\ingroup MATHTOOLS
	 * <remarks> assumes matrix is a world matrix composed of translation, rotation and scale. </remarks>
	 *
	 * <param name="worldMatrix"> The world matrix.</param>
	 *
	 * <returns> The Z scale.</returns>
	 **************************************************************************************************/
	float ExtractScaleZ(const Matrix& worldMatrix);

	/**********************************************************************************************//**
	 * <summary> Extracts translation matrix from world matrix.</summary>
	 *	\ingroup MATHTOOLS
	 * <remarks> assumes matrix is a world matrix composed of translation, rotation and scale.</remarks>
	 *
	 * <param name="worldMatrix"> The world matrix.</param>
	 *
	 * <returns> The translation matrix.</returns>
	 **************************************************************************************************/
	Matrix ExtractTranslationMatrix(const Matrix& worldMatrix);

	/**********************************************************************************************//**
	 * <summary> Extract translation vector from world matrix.</summary>
	 *	\ingroup MATHTOOLS
	 * <remarks> assumes matrix is a world matrix composed of translation, rotation and scale.</remarks>
	 *
	 * <param name="worldMatrix"> The world matrix.</param>
	 *
	 * <returns> The translation vector.</returns>
	 **************************************************************************************************/
	Vect ExtractTranslationXYZ(const Matrix& worldMatrix);

	/**********************************************************************************************//**
	* <summary> Computes rotation matrix to rotate vector from current to target.</summary>
	*	\ingroup MATHTOOLS
	* <remarks> .</remarks>
	*
	* <param name="current"> A Vect.</param>
	* <param name="target"> A Vect.</param>
	* <returns> a rotation matrix.</returns>
	**************************************************************************************************/
	Matrix RotationFromTowards(const Vect& current, const Vect& target);

	// Vect functions

	/**********************************************************************************************//**
	* <summary> Multiplies two vectors by each component (x1 * x2, y1 * y2, z1 * z2).</summary>
	*	\ingroup MATHTOOLS
	* <remarks> </remarks>
	*
	* <param name="vect_1"> A Vect.</param>
	* <param name="vect_2"> A Vect.</param>
	*
	* <returns> A Vect</returns>
	**************************************************************************************************/
	Vect MultiplyComponents(const Vect& vect_1, const Vect& vect_2);

	/**********************************************************************************************//**
	* <summary> Constructs Vect using the mininum values of two Vects.</summary>
	*	\ingroup MATHTOOLS
	* <remarks> </remarks>
	*
	* <param name="vect_1"> A Vect.</param>
	* <param name="vect_2"> A Vect.</param>
	*
	* <returns> Vect with minimum values.</returns>
	**************************************************************************************************/
	Vect Min(const Vect& vect_1, const Vect& vect_2);

	/**********************************************************************************************//**
	* <summary> Constructs Vect using the maximum values of two Vects.</summary>
	*	\ingroup MATHTOOLS
	* <remarks> </remarks>
	*
	* <param name="vect_1"> A Vect.</param>
	* <param name="vect_2"> A Vect.</param>
	*
	* <returns> Vect with maximum values.</returns>
	**************************************************************************************************/
	Vect Max(const Vect& vect_1, const Vect& vect_2);

	/**********************************************************************************************//**
	* <summary> Clamps the given Vect .</summary>
	*
	* <param name="value"> The value.</param>
	* <param name="min">   The minimum.</param>
	* <param name="max">   The maximum.</param>
	*
	* <returns> A vector.</returns>
	**************************************************************************************************/
	Vect Clamp(const Vect& value, const Vect& min, const Vect& max);

	/**********************************************************************************************//**
	* <summary> Projection of vect_1 onto vect_2.</summary>
	*
	* <param name="vect_1">   A Vect.</param>
	* <param name="vect_2">   A vect.</param>
	*
	* <returns> The projection vect.</returns>
	**************************************************************************************************/
	Vect Projection(const Vect& vect_1, const Vect& vect_2);

	/**********************************************************************************************//**
	* <summary> Projection length of vect_1 onto vect_2.</summary>
	*
	* <param name="vect_1">   A Vect.</param>
	* <param name="vect_2">   A vect.</param>
	*
	* <returns> The projection length.</returns>
	**************************************************************************************************/
	float ProjectionLength(const Vect& vect_1, const Vect& vect_2);

	/**********************************************************************************************//**
	 * <summary> raises base to the power of integers.</summary>
	 *	\ingroup MATHTOOLS
	 * <param name="base"> The base.</param>
	 * <param name="exponent"> An interger exponent.</param>
	 *
	 * <returns> A type.</returns>
	 **************************************************************************************************/
	float power(float base, int exponent);

	/**********************************************************************************************//**
	 * <summary> Clamp the given value.</summary>
	 *
	 * <typeparam name="type"> Type of the type.</typeparam>
	 * <param name="value"> The value.</param>
	 * <param name="min">   The minimum.</param>
	 * <param name="max">   The maximum.</param>
	 *
	 * <returns> A type.</returns>
	 **************************************************************************************************/
	template<typename type>
	type Clamp(type value, type min, type max)
	{
		return std::max(min, std::min(value, max));
	}

	/**********************************************************************************************//**
	* <summary> Determines if a Vect is in between two Vect values</summary>
	*	\ingroup MATHTOOLS
	* <remarks> </remarks>
	*
	* <param name="vect"> A Vect.</param>
	* <param name="vect_1"> A Vect.</param>
	* <param name="vect_2"> A Vect.</param>
	*
	* <returns> True if within range, otherwise false.</returns>
	**************************************************************************************************/
	bool IsInRange(const Vect& vect, const Vect& vect_1, const Vect& vect_2);

	bool IsInRange(float number, float number_1, float number_2);

	/**********************************************************************************************//**
	* <summary> Determines if a Vect is less than another Vect. </summary>
	*	\ingroup MATHTOOLS
	* <remarks> </remarks>
	*
	* <param name="vect_1"> A Vect.</param>
	* <param name="vect_2"> A Vect.</param>
	*
	* <returns> True if less than , otherwise false. </returns>
	**************************************************************************************************/
	bool IsLessThan(const Vect& vect_1, const Vect& vect_2);

	/**********************************************************************************************//**
	* <summary> Determines if a Vect is greater than another Vect. </summary>
	*	\ingroup MATHTOOLS
	* <remarks> </remarks>
	*
	* <param name="vect_1"> A Vect.</param>
	* <param name="vect_2"> A Vect.</param>
	*
	* <returns> True if greater than , otherwise false. </returns>
	**************************************************************************************************/
	bool IsGreaterThan(const Vect& vect_1, const Vect& vect_2);

	// Others

	struct Interval
	{
		Interval(float start, float end)
			: _start(start), _end(end)
		{
			assert(start <= end);
		}

		float _start;
		float _end;
	};

	/**********************************************************************************************//**
	* <summary> Determines if two intervals overlap</summary>
	*	\ingroup MATHTOOLS
	* <remarks> Uses MathTools::Interval struct testing intervals</remarks>
	*
	* <param name="interval_1"> An interval. </param>
	* <param name="interval_2"> An interval. </param>
	*
	* <returns> True if intervals overlap, otherwise false.</returns>
	**************************************************************************************************/
	bool DoIntervalsOverlap(const Interval& interval_1, const Interval& interval_2);
};

#endif // !_MathTools

//-----------------------------------------------------------------------------------------------------------------------------
// MathTools Comment Template
//-----------------------------------------------------------------------------------------------------------------------------