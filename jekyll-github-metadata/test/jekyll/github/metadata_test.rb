require "test_helper"

class Jekyll::Github::MetadataTest < Minitest::Test
  def test_that_it_has_a_version_number
    refute_nil ::Jekyll::Github::Metadata::VERSION
  end

  def test_it_does_something_useful
    assert false
  end
end
