class Fetch {
  get = async(url) =>{ //can be either findCourses or findCourseByID
    try {
      let resp = await fetch(url);
      let result = await resp.json();
      return result;
    } catch (error) {
      return 0;
    }finally{}
  }
  post = async(url, content) =>{ //Can only be AddCourse
    try {
      let resp = await fetch(url, {
        method: 'POST',
        body: JSON.stringify(content)
      });
      let result = await resp.json();
      return result;
    } catch (error) {
      return 0;
    }finally{}
  }
  delete = async(url) =>{
    try {
      let resp = await fetch(url, {
        method: 'DELETE',
      });
      let result = await resp.json();
      return result;
    } catch (error) {
      return 0;
    }finally{}
  }
}

export const fetch_obj = new Fetch();