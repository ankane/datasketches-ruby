require_relative "test_helper"

class ThetaSketchTest < Minitest::Test
  def test_update
    sketch = DataSketches::UpdateThetaSketch.new(14)
    assert sketch.empty?

    sketch.update(1)
    sketch.update(2.0)
    sketch.update("three")
    assert_in_delta 3, sketch.estimate
    assert !sketch.empty?

    assert_in_delta 3, sketch.lower_bound(1)
    assert_in_delta 3, sketch.upper_bound(1)

    assert_kind_of DataSketches::CompactThetaSketch, sketch.compact
  end

  def test_union
    a = DataSketches::UpdateThetaSketch.new(14)
    %w(a b c).each { |v| a.update(v) }

    b = DataSketches::UpdateThetaSketch.new(14)
    %w(b c d).each { |v| b.update(v) }

    u = DataSketches::ThetaUnion.new
    u.update(a)
    u.update(b)
    assert_in_delta 4, u.result.estimate
  end

  def test_intersection
    a = DataSketches::UpdateThetaSketch.new(14)
    %w(a b c).each { |v| a.update(v) }

    b = DataSketches::UpdateThetaSketch.new(14)
    %w(b c d).each { |v| b.update(v) }

    i = DataSketches::ThetaIntersection.new
    i.update(a)
    i.update(b)
    assert i.result?
    assert_in_delta 2, i.result.estimate
  end

  def test_a_not_b
    a = DataSketches::UpdateThetaSketch.new(14)
    %w(a b c).each { |v| a.update(v) }

    b = DataSketches::UpdateThetaSketch.new(14)
    %w(b c d).each { |v| b.update(v) }

    d = DataSketches::ThetaANotB.new
    d.compute(a, b)
  end
end
