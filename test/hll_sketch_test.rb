require_relative "test_helper"

class HllSketchTest < Minitest::Test
  def test_works
    sketch = DataSketches::HllSketch.new(14)
    assert_equal 14, sketch.lg_config_k
    assert !sketch.compact?
    assert sketch.empty?

    sketch.update(1)
    sketch.update(2.0)
    sketch.update("three")
    assert_in_delta 3, sketch.estimate
    assert !sketch.empty?

    data = sketch.serialize_compact
    assert_equal 20, data.bytesize
    sketch = DataSketches::HllSketch.deserialize(data)
    assert_in_delta 3, sketch.estimate

    data = sketch.serialize_updatable
    assert_equal 40, data.bytesize
    sketch = DataSketches::HllSketch.deserialize(data)
    assert_in_delta 3, sketch.estimate
  end

  def test_bignum
    sketch = DataSketches::HllSketch.new(14)
    sketch.update(2**64)
  end
end
