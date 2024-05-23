const express = require('express');
const {ConvosController} = require('./ConvosController');

const router = express.Router();

router.get('/', ConvosController.findConvos);
router.get('/:id', ConvosController.findConvoById);

module.exports = router;