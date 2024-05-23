const express = require('express');
const {CoursesController} = require('./CoursesController');

const router = express.Router();

router.get('/', CoursesController.findCourses);
router.get('/:id', CoursesController.findCourseById);
router.post('/', CoursesController.addCourse);
router.delete('/:id', CoursesController.deleteCourse);
router.get('/courses/', CoursesController.findCourses);

module.exports = router;