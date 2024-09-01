#ifndef PHTREE_H
#define PHTREE_H

#include <godot_cpp/classes/node.hpp>
#include <phtree/phtree.h>


#ifdef REAL_T_IS_DOUBLE
typedef int64_t scalar_real_t;
#else
typedef int32_t scalar_real_t;
#endif

namespace improbable::phtree {

class ConverterGD2 : public ConverterBase<2, 2, real_t, scalar_real_t, godot::Vector2, godot::Rect2> {
    using BASE = ConverterPointBase<2, real_t, scalar_real_t>;
    using PointInternal = typename BASE::KeyInternal;
    using QueryBoxInternal = typename BASE::QueryBoxInternal;

  public:
  	explicit ConverterGD2() {}

    [[nodiscard]] PointInternal pre(const godot::Vector2& point) const {
        return { ScalarConverterIEEE::pre(point.x),
                 ScalarConverterIEEE::pre(point.y) };
    }

    [[nodiscard]] godot::Vector2 post(const PointInternal& in) const {
        return { (real_t) ScalarConverterIEEE::post(in[0]), 
        		 (real_t) ScalarConverterIEEE::post(in[1]) };
    }

    [[nodiscard]] QueryBoxInternal pre_query(const godot::Rect2& box) const {
        return { pre(box.position), pre(box.get_end()) };
    }
};

using PhTreeGDVector2 = PhTreeD<2, godot::Node*, ConverterGD2>;

struct DistanceEuclideanGD {
    double operator()(const godot::Vector2& p1, const godot::Vector2& p2) const noexcept {
        return p1.distance_to(p2);
    };
};
class DistanceMomentumGD {
  private:
  	godot::Vector2 momentum;
  public:
	DistanceMomentumGD(godot::Vector2 p_momentum = godot::Vector2()):  momentum(p_momentum) {}
    double operator()(const godot::Vector2& p1, const godot::Vector2& p2) const noexcept {
        // copied from the old DistanceEuclideanGD
        // TODO make it do the thing
        double sum2 = 0;
        double x2 = p1.x - p2.x;
        double y2 = p1.y - p2.y;
        sum2 += x2 * x2;
        sum2 += y2 * y2;
        return sqrt(sum2);
    };
};

using FilterSphereGD = FilterSphere<ConverterGD2, DistanceEuclideanGD>;

} // namespace improbable::phtree


namespace godot {

class PHTree : public Node {
	GDCLASS(PHTree, Node)

private:
	improbable::phtree::ConverterGD2 converter;
	improbable::phtree::DistanceEuclideanGD dist_fn;
	improbable::phtree::PhTreeGDVector2 tree;

protected:
	static void _bind_methods();

public:
	PHTree();
	~PHTree();
    void _ready( ) override;
	bool insert_node(Vector2 position, Node* node);
	bool relocate_node(Vector2 old_position, Vector2 new_position);
	bool erase_node(Vector2 position);
	Node* get_nearest(Vector2 p_position);
	TypedArray<Node> get_k_nearest(int k, Vector2 p_position );
	TypedArray<Node> get_window(Rect2 p_box );
	TypedArray<Node> get_radius( Vector2 p_position, real_t p_radius );

};
} // namespace godot

#endif // PHTREE_H