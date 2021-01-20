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

    serialized = sketch.serialize_compact
    assert_equal 20, serialized.bytesize
    sketch = DataSketches::HllSketch.deserialize(serialized)
    assert_in_delta 3, sketch.estimate

    serialized = sketch.serialize_updatable
    assert_equal 40, serialized.bytesize
    sketch = DataSketches::HllSketch.deserialize(serialized)
    assert_in_delta 3, sketch.estimate
  end
end
