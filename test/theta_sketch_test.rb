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

    data = sketch.serialize
    assert_equal 1048, data.bytesize

    sketch = DataSketches::UpdateThetaSketch.deserialize(data)
    assert_in_delta 3, sketch.estimate

    assert_kind_of DataSketches::CompactThetaSketch, sketch.compact(true)
  end
end
